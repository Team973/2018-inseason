#include "src/subsystems/IntakeAssembly.h"
#include "WPILib.h"
#include "ctre/Phoenix.h"
#include "lib/util/WrapDash.h"
#include <cmath>

using namespace frc;

namespace frc973 {
IntakeAssembly::IntakeAssembly(TaskMgr *scheduler, LogSpreadsheet *logger,
                               ObservableJoystick *operatorJoystick,
                               Elevator *elevator, Claw *claw, Wrist *wrist,
                               GreyLight *greylight)
        : m_scheduler(scheduler)
        , m_operatorJoystick(operatorJoystick)
        , m_elevator(elevator)
        , m_claw(claw)
        , m_wrist(wrist)
        , m_greyLight(greylight)
        , m_intakeSignal(
              new LightPattern::Flash(INTAKE_GREEN, NO_COLOR, 50, 15))
        , m_controlMode(ControlMode::Idle)
        , m_endPositionGoal(STOW_PRESET)
        , m_interimPositionGoal(STOW_PRESET) {
    this->m_scheduler->RegisterTask("IntakeAssembly", this, TASK_PERIODIC);
}

IntakeAssembly::~IntakeAssembly() {
    m_scheduler->UnregisterTask(this);
}

const IntakeAssembly::IntakePreset IntakeAssembly::STOW_PRESET =
    IntakeAssembly::IntakePreset(Elevator::GROUND, Wrist::STOW);
const IntakeAssembly::IntakePreset IntakeAssembly::GROUND_PRESET =
    IntakeAssembly::IntakePreset(Elevator::GROUND, Wrist::EXTENDED);
const IntakeAssembly::IntakePreset IntakeAssembly::VAULT_PRESET =
    IntakeAssembly::IntakePreset(Elevator::VAULT, Wrist::EXTENDED);
const IntakeAssembly::IntakePreset IntakeAssembly::LOW_GOAL_PRESET =
    IntakeAssembly::IntakePreset(Elevator::LOW_GOAL, Wrist::EXTENDED);
const IntakeAssembly::IntakePreset IntakeAssembly::SCALE_LOW_PRESET =
    IntakeAssembly::IntakePreset(Elevator::SCALE_LOW, Wrist::SCALE);
const IntakeAssembly::IntakePreset IntakeAssembly::SCALE_MID_PRESET =
    IntakeAssembly::IntakePreset(Elevator::SCALE_MID, Wrist::SCALE);
const IntakeAssembly::IntakePreset IntakeAssembly::SCALE_HIGH_PRESET =
    IntakeAssembly::IntakePreset(Elevator::SCALE_HIGH, Wrist::SCALE);
const IntakeAssembly::IntakePreset IntakeAssembly::OVER_BACK_PRESET =
    IntakeAssembly::IntakePreset(Elevator::SCALE_HIGH, Wrist::OVER_THE_BACK);
const IntakeAssembly::IntakePreset IntakeAssembly::SECOND_STACK_PRESET =
    IntakeAssembly::IntakePreset(20.0, Wrist::EXTENDED);
const IntakeAssembly::IntakePreset IntakeAssembly::HANGING_PRESET =
    IntakeAssembly::IntakePreset(61.5, -75);
const IntakeAssembly::IntakePreset IntakeAssembly::HALF_STOW_PRESET =
    IntakeAssembly::IntakePreset(Elevator::GROUND, Wrist::SCALE);

void IntakeAssembly::GoToIntakePosition(IntakePreset intakePosition) {
    m_endPositionGoal = intakePosition;

    if (intakePosition == OVER_BACK_PRESET) {
        if (GetElevatorPosition() >= 77.0) {
            m_controlMode = ControlMode::OverBackPosition;
        }
        else if (GetElevatorPosition() >= 72.0 && GetWristPosition() >= 20.0) {
            m_controlMode = ControlMode::SuperForkPosition;
        }
        else {
            m_controlMode = ControlMode::SubForkPosition;
        }
    }
    else {
        if (GetElevatorPosition() >= 77.0 && GetWristPosition() <= 20.0 &&
            intakePosition.elevatorPosition < 77) {
            m_controlMode = ControlMode::SuperForkPosition;
        }
        else if (GetElevatorPosition() >= 72 &&
                 intakePosition.elevatorPosition < 72) {
            m_controlMode = ControlMode::SubForkPosition;
        }
        else {
            m_controlMode = ControlMode::LowPosition;
        }
    }
}

void IntakeAssembly::SetPosition(IntakePreset preset) {
    m_interimPositionGoal = preset;
    m_elevator->SetPosition(preset.elevatorPosition);
    m_wrist->SetPosition(preset.wristPosition);
}

void IntakeAssembly::SetElevatorManualPower(double input) {
    m_controlMode = ControlMode::ManualVoltage;
    m_elevator->SetPower(input);
}

void IntakeAssembly::SetWristManualPower(double input) {
    m_controlMode = ControlMode::ManualVoltage;
    m_wrist->SetPower(input);
}

void IntakeAssembly::SetPosManualInput() {
    if (m_controlMode != ControlMode::HangingAuto and
        m_controlMode != ControlMode::HangingManual) {
        if (m_controlMode != ControlMode::ManualPosition) {
            m_interimPositionGoal.wristPosition = GetWristPosition();
        }
        m_controlMode = ControlMode::ManualPosition;
    }
    else if (m_controlMode == ControlMode::HangingAuto) {
        m_controlMode = ControlMode::HangingManual;
    }
}

void IntakeAssembly::SetModeHanging(bool hanging) {
    if (hanging) {
        if (m_elevator->GetPosition() < 40.0) {
            m_controlMode = ControlMode::PreHanging;
        }
        else {
            m_controlMode = ControlMode::HangingAuto;
        }
    }
    else {
        m_controlMode = ControlMode::ManualPosition;
    }
}

void IntakeAssembly::RunIntake(double power) {
    m_claw->RunIntake(power);
}

void IntakeAssembly::FastEjectCube() {
    m_claw->EjectCube(1.0);
}

void IntakeAssembly::EjectCube() {
    m_claw->EjectCube(0.75);
}

void IntakeAssembly::SlowEjectCube() {
    m_claw->EjectCube(0.5);
}

void IntakeAssembly::HaltIntake() {
    m_claw->EjectCube(0.0);
}

void IntakeAssembly::HoldCube() {
    m_claw->HoldCube();
}

void IntakeAssembly::StopIntake() {
    m_claw->StopIntake();
}

void IntakeAssembly::OpenClaw() {
    m_claw->OpenClaw();
}

void IntakeAssembly::SoftCloseClaw() {
    m_claw->SoftCloseClaw();
}

void IntakeAssembly::HardCloseClaw() {
    m_claw->HardCloseClaw();
}

double IntakeAssembly::GetElevatorPosition() {
    return m_elevator->GetPosition();
}

double IntakeAssembly::GetWristPosition() {
    return m_wrist->GetPosition();
}

void IntakeAssembly::ZeroPosition() {
    m_elevator->ZeroPosition();
    m_wrist->ZeroPosition();
}

void IntakeAssembly::EnableBrakeMode() {
    m_elevator->EnableBrakeMode();
}

void IntakeAssembly::EnableCoastMode() {
    m_elevator->EnableCoastMode();
}

const Wrist *IntakeAssembly::GetWrist() {
    return m_wrist;
}

const Claw *IntakeAssembly::GetClaw() {
    return m_claw;
}

const Elevator *IntakeAssembly::GetElevator() {
    return m_elevator;
}

double IntakeAssembly::GetWristLowerBound(double elevatorPosition) {
    if (elevatorPosition >= FORK_AVOIDANCE_MAX_HEIGHT) {
        return OVER_BACK_FORK_LOWER_BOUND;
    }
    else if (elevatorPosition < FORK_AVOIDANCE_MAX_HEIGHT &&
             elevatorPosition >= FORK_AVOIDANCE_MID_HEIGHT) {
        return NOCOLLIDE_FORK_LOWER_BOUND;
    }
    else if (elevatorPosition >= FORK_AVOIDANCE_MIN_HEIGHT &&
             elevatorPosition < FORK_AVOIDANCE_MID_HEIGHT) {
        const double wristBoundDiff =
            NOCOLLIDE_FORK_LOWER_BOUND - SWITCH_LOWER_BOUND;
        const double elevatorPosDiff =
            FORK_AVOIDANCE_MID_HEIGHT - FORK_AVOIDANCE_MIN_HEIGHT;

        /* ref slope intercept form */
        return (elevatorPosition - FORK_AVOIDANCE_MIN_HEIGHT) *
                   (wristBoundDiff / elevatorPosDiff) +
               SWITCH_LOWER_BOUND;
    }
    else if (elevatorPosition < FORK_AVOIDANCE_MIN_HEIGHT) {
        return SWITCH_LOWER_BOUND;
    }
    else {
        return SWITCH_LOWER_BOUND;
    }
}

double IntakeAssembly::GetPositionError() {
    return sqrt(
        pow(m_interimPositionGoal.elevatorPosition - GetElevatorPosition(), 2) +
        pow(m_interimPositionGoal.wristPosition - GetWristPosition(), 2));
}

double IntakeAssembly::GetEndPositionError() {
    return sqrt(
        pow(m_endPositionGoal.elevatorPosition - GetElevatorPosition(), 2) +
        pow(m_endPositionGoal.wristPosition - GetWristPosition(), 2));
}

void IntakeAssembly::StartZeroPosition() {
    m_controlMode = ControlMode::Zeroing;
}

void IntakeAssembly::EndZeroPosition() {
    m_elevator->ZeroPosition();
    m_wrist->ZeroPosition();
}

void IntakeAssembly::Flash() {
    m_intakeSignal->Reset();
    m_greyLight->SetPixelStateProcessor(m_intakeSignal);
}

void IntakeAssembly::TaskPeriodic(RobotMode mode) {
    DBStringPrintf(DBStringPos::DB_LINE8, "w %3.2f s %3.2f e %3.2f",
                   GetWristPosition(), m_interimPositionGoal.wristPosition,
                   GetPositionError());

    switch (m_controlMode) {
        case ControlMode::Idle:
            break;
        case ControlMode::ManualPosition: {
            double elevatorInput =
                -m_operatorJoystick->GetRawAxis(DualAction::LeftYAxis);
            double wristInc = pow(-m_operatorJoystick->GetRawAxisWithDeadband(
                                      DualAction::RightXAxis),
                                  3);
            double wristPosGoal = m_interimPositionGoal.wristPosition;

            if (wristInc < 0.0) {
                m_wrist->m_wristMotor->ConfigContinuousCurrentLimit(10, 0);
                wristInc *= 3.0;
            }
            else {
                m_wrist->m_wristMotor->ConfigContinuousCurrentLimit(5, 0);
            }

            if (GetElevatorPosition() > 78.0 &&
                GetWristPosition() < NOCOLLIDE_FORK_LOWER_BOUND &&
                elevatorInput < 0.0) {
                wristPosGoal = NOCOLLIDE_FORK_LOWER_BOUND;
                elevatorInput = 0.0;
            }
            else {
                wristPosGoal += wristInc * MAX_WRIST_SPEED * 1.0 / 20.0;
                wristPosGoal = Util::bound(
                    wristPosGoal,
                    GetWristPosition() - MAX_WRIST_SPEED * 3 / 20.0,
                    GetWristPosition() + MAX_WRIST_SPEED * 1.5 / 20.0);
            }

            m_wrist->SetPositionStep(Util::bound(
                wristPosGoal, GetWristLowerBound(GetElevatorPosition()),
                UPPER_WRIST_BOUND));
            m_elevator->SetPower(elevatorInput +
                                 Elevator::ELEVATOR_FEED_FORWARD);

            m_interimPositionGoal.wristPosition = wristPosGoal;
        } break;
        case ControlMode::PreHanging:
            m_elevator->SetPosition(36.0);
            m_wrist->SetPosition(-30.0);
            m_claw->OpenClaw();
            m_claw->StopIntake();
            if (m_elevator->GetPosition() > 34.0) {
                m_controlMode = ControlMode::MidHanging;
            }
            break;
        case ControlMode::MidHanging:
            m_wrist->SetPosition(-80.0);
            if (m_wrist->GetPosition() < -70.0) {
                m_controlMode = ControlMode::HangingAuto;
            }
            break;
        case ControlMode::HangingAuto:
            m_claw->OpenClaw();
            m_claw->StopIntake();
            SetPosition(HANGING_PRESET);
            m_wrist->m_wristMotor->ConfigContinuousCurrentLimit(5, 0);
            if (GetPositionError() < 5.0) {
                m_controlMode = ControlMode::HangingManual;
            }
            break;
        case ControlMode::HangingManual: {
            double elevatorInput =
                -m_operatorJoystick->GetRawAxis(DualAction::LeftYAxis);
            m_wrist->m_wristMotor->ConfigContinuousCurrentLimit(5, 0);
            if (m_elevator->GetPosition() > 46.0) {
                m_wrist->SetPosition(HANGING_PRESET.wristPosition);
            }
            else {
                m_wrist->SetPosition(-30.0);
            }
            m_claw->OpenClaw();
            m_claw->StopIntake();
            m_elevator->SetPower(elevatorInput +
                                 Elevator::ELEVATOR_FEED_FORWARD);
        } break;
        case ControlMode::ManualVoltage: {
            double elevatorInput =
                -m_operatorJoystick->GetRawAxis(DualAction::LeftYAxis);
            double wristInput = -m_operatorJoystick->GetRawAxisWithDeadband(
                DualAction::RightXAxis);

            m_wrist->SetPower(wristInput);
            m_elevator->SetPower(elevatorInput +
                                 Elevator::ELEVATOR_FEED_FORWARD);
        } break;
        case ControlMode::LowPosition:
            SetPosition(m_endPositionGoal);
            break;
        case ControlMode::SubForkPosition:
            SetPosition(SCALE_LOW_PRESET);

            if (GetPositionError() < 15.0) {
                if (m_endPositionGoal == OVER_BACK_PRESET) {
                    m_controlMode = ControlMode::SuperForkPosition;
                }
                else {
                    m_controlMode = ControlMode::LowPosition;
                }
            }
            break;
        case ControlMode::SuperForkPosition:
            SetPosition(SCALE_HIGH_PRESET);

            if (GetPositionError() < 15.0) {
                if (m_endPositionGoal == OVER_BACK_PRESET) {
                    m_controlMode = ControlMode::OverBackPosition;
                }
                else if (m_endPositionGoal == SCALE_HIGH_PRESET) {
                    m_controlMode = ControlMode::LowPosition;
                }
                else {
                    m_controlMode = ControlMode::SubForkPosition;
                }
            }
            break;
        case ControlMode::OverBackPosition:
            SetPosition(OVER_BACK_PRESET);
            break;
        case ControlMode::Zeroing:
            m_elevator->SetPower(-0.1);
            m_wrist->SetPower(0.2);
            break;
    }
}
}
