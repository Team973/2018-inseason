#include "src/subsystems/IntakeAssembly.h"
#include "WPILib.h"
#include "ctre/Phoenix.h"
#include "lib/util/WrapDash.h"
#include <cmath>

using namespace frc;

namespace frc973 {
IntakeAssembly::IntakeAssembly(TaskMgr *scheduler, LogSpreadsheet *logger,
                               ObservableJoystick *operatorJoystick,
                               Elevator *elevator, Wrist *wrist,
                               GreyLight *greylight)
        : m_scheduler(scheduler)
        , m_operatorJoystick(operatorJoystick)
        , m_elevator(elevator)
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

void IntakeAssembly::GoToIntakePosition(IntakePreset intakePosition) {
    m_endPositionGoal = intakePosition;
    m_wrist->CloseClaw();

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
        if (GetElevatorPosition() >= 77.0) {
            m_controlMode = ControlMode::SuperForkPosition;
        }
        else if (GetElevatorPosition() >= 72) {
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
    m_elevator->SetPower(input);
}

void IntakeAssembly::SetWristManualPower(double input) {
    m_wrist->SetPower(input);
}

void IntakeAssembly::SetPosManualInput() {
    m_controlMode = ControlMode::ManualPosition;
}

void IntakeAssembly::IntakeCube(double power) {
    m_controlMode = ControlMode::SwitchIntaking;
    m_wrist->IntakeCube(power);
    m_wrist->CloseClaw();
}

void IntakeAssembly::VaultIntake() {
    m_controlMode = ControlMode::VaultStart;
    m_wrist->IntakeCube(-1.0);
    m_wrist->CloseClaw();
}

void IntakeAssembly::EjectCube() {
    m_wrist->EjectCube();
    m_controlMode = ControlMode::ManualPosition;
}

void IntakeAssembly::StopIntake() {
    m_wrist->StopIntake();
    m_controlMode = ControlMode::ManualPosition;
}

void IntakeAssembly::DropCube() {
    m_wrist->OpenClaw();
    m_controlMode = ControlMode::ManualPosition;
}

void IntakeAssembly::GrabCube() {
    m_wrist->CloseClaw();
    m_controlMode = ControlMode::ManualPosition;
}

double IntakeAssembly::GetElevatorPosition() {
    return m_elevator->GetPosition();
}

double IntakeAssembly::GetWristPosition() {
    return m_wrist->GetPosition();
}

void IntakeAssembly::EnableBrakeMode() {
    m_elevator->EnableBrakeMode();
}

void IntakeAssembly::EnableCoastMode() {
    m_elevator->EnableCoastMode();
}

double IntakeAssembly::GetWristLowerBound(double elevatorPosition) {
    if (elevatorPosition >= 78.0) {
        return OVER_BACK_FORK_LOWER_BOUND;
    }
    else if (elevatorPosition < 78.0 && elevatorPosition >= 31.0) {
        return NOCOLLIDE_FORK_LOWER_BOUND;
    }
    else if (elevatorPosition < 31.0 && elevatorPosition >= 20.0) {
        return ((10.0 - (-40.0)) / (33.0 - 20.0) * (elevatorPosition - 31.0) +
                10.0);
    }
    else if (elevatorPosition < 20.0) {
        return SWITCH_LOWER_BOUND;
    }
    else {
        return SWITCH_LOWER_BOUND;
    }
}

double IntakeAssembly::GetPositionError() {
    return sqrt(
        pow(m_endPositionGoal.elevatorPosition - GetElevatorPosition(), 2) +
        pow(m_endPositionGoal.wristPosition - GetWristPosition(), 2));
}

void IntakeAssembly::TaskPeriodic(RobotMode mode) {
    DBStringPrintf(DBStringPos::DB_LINE8, "w %3.2f s %3.2f", GetWristPosition(),
                   m_interimPositionGoal.wristPosition);

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

            if (GetElevatorPosition() > 78.0 &&
                GetWristPosition() < NOCOLLIDE_FORK_LOWER_BOUND &&
                elevatorInput < 0.0) {
                wristPosGoal = NOCOLLIDE_FORK_LOWER_BOUND;
                elevatorInput = 0.0;
            }
            else {
                m_interimPositionGoal.wristPosition +=
                    wristInc * MAX_WRIST_SPEED * 1.0 / 20.0;
                wristPosGoal = Util::bound(
                    wristPosGoal,
                    GetWristPosition() - MAX_WRIST_SPEED * 1.5 / 20.0,
                    GetWristPosition() + MAX_WRIST_SPEED * 1.5 / 20.0);
            }

            m_wrist->SetPositionStep(Util::bound(
                wristPosGoal, GetWristLowerBound(GetElevatorPosition()),
                UPPER_WRIST_BOUND));
            m_elevator->SetPower(elevatorInput + ELEVATOR_FEED_FORWARD);

            m_interimPositionGoal.wristPosition = wristPosGoal;
        } break;
        case ControlMode::ManualVoltage: {
            double elevatorInput =
                -m_operatorJoystick->GetRawAxis(DualAction::LeftYAxis);
            double wristInput = -m_operatorJoystick->GetRawAxisWithDeadband(
                DualAction::RightXAxis);

            m_wrist->SetPower(wristInput);
            m_elevator->SetPower(elevatorInput + ELEVATOR_FEED_FORWARD);
        } break;
        case ControlMode::LowPosition:
            SetPosition(m_endPositionGoal);
            break;
        case ControlMode::SubForkPosition:
            SetPosition(SCALE_LOW_PRESET);

            if (GetPositionError() < 5.0) {
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

            if (GetPositionError() < 5.0) {
                if (m_endPositionGoal == OVER_BACK_PRESET) {
                    m_controlMode = ControlMode::OverBackPosition;
                }
                else {
                    m_controlMode = ControlMode::SubForkPosition;
                }
            }
            break;
        case ControlMode::OverBackPosition:
            SetPosition(OVER_BACK_PRESET);
            break;
        case ControlMode::SwitchIntaking:
            GoToIntakePosition(GROUND_PRESET);
            if (GetElevatorPosition() < 5.0) {
                m_controlMode = ControlMode::SwitchStandby;
            }
            break;
        case ControlMode::SwitchStandby:
            if (m_wrist->IsCubeIn() ||
                m_operatorJoystick->GetRawButton(DualAction::Back)) {
                GoToIntakePosition(STOW_PRESET);
                m_wrist->StopIntake();
                m_intakeSignal->Reset();
                m_greyLight->SetPixelStateProcessor(m_intakeSignal);
            }
            break;
        case ControlMode::VaultStart:
            GoToIntakePosition(GROUND_PRESET);
            m_wrist->IntakeCube(-1.0);
            m_controlMode = ControlMode::VaultStop;
            break;
        case ControlMode::VaultStop:
            if (m_wrist->IsCubeIn()) {
                StopIntake();
            }
            break;
    }
}
}
