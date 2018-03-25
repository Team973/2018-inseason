#include "src/subsystems/IntakeAssembly.h"
#include "WPILib.h"
#include "ctre/Phoenix.h"
#include "lib/util/WrapDash.h"

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
        , m_collisionAvoidanceMode(CollisionAvoidanceMode::low)
        , m_elevatorPositionSetpoint(0.0)
        , m_wristPositionSetpoint(0.0)
        , m_elevatorInc(0.0)
        , m_wristInc(0.0) {
    this->m_scheduler->RegisterTask("IntakeAssembly", this, TASK_PERIODIC);
}

IntakeAssembly::~IntakeAssembly() {
    m_scheduler->UnregisterTask(this);
}

void IntakeAssembly::GoToIntakePosition(IntakePosition intakePosition) {
    m_controlMode = ControlMode::Position;
    switch (intakePosition) {
        case IntakePosition::stow:
            m_elevatorPositionSetpoint = Elevator::GROUND;
            m_wristPositionSetpoint = Wrist::STOW;
            break;
        case IntakePosition::ground:
            m_elevatorPositionSetpoint = Elevator::GROUND;
            m_wristPositionSetpoint = Wrist::EXTENDED;
            break;
        case IntakePosition::vault:
            m_elevatorPositionSetpoint = Elevator::VAULT;
            m_wristPositionSetpoint = Wrist::EXTENDED;
            break;
        case IntakePosition::lowGoal:
            m_elevatorPositionSetpoint = Elevator::LOW_GOAL;
            m_wristPositionSetpoint = Wrist::EXTENDED;
            break;
        case IntakePosition::scaleLow:
            m_elevatorPositionSetpoint = Elevator::SCALE_LOW;
            m_wristPositionSetpoint = Wrist::SCALE;
            break;
        case IntakePosition::scaleMid:
            m_elevatorPositionSetpoint = Elevator::SCALE_MID;
            m_wristPositionSetpoint = Wrist::SCALE;
            break;
        case IntakePosition::scaleHigh:
            m_elevatorPositionSetpoint = Elevator::SCALE_HIGH;
            m_wristPositionSetpoint = Wrist::SCALE;
            break;
        case IntakePosition::overBack:
            m_elevatorPositionSetpoint = Elevator::SCALE_HIGH;
            m_wristPositionSetpoint = Wrist::OVER_THE_BACK;
            break;
        default:
            break;
    }
    m_elevator->SetPosition(m_elevatorPositionSetpoint);
    m_wrist->SetPosition(m_wristPositionSetpoint);
    m_wrist->CloseClaw();
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
    m_controlMode = ControlMode::switchIntaking;
    m_wrist->IntakeCube(power);
    m_wrist->CloseClaw();
}

void IntakeAssembly::VaultIntake() {
    m_controlMode = ControlMode::vaultStart;
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
    if (elevatorPosition > 78.0) {
        return OVER_BACK_LOWER_BOUND;
    }
    else if (elevatorPosition < 78.0 && elevatorPosition > 31.0) {
        return FORK_LOWER_BOUND;
    }
    else if (elevatorPosition < 31.0 && elevatorPosition > 20.0) {
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

void IntakeAssembly::TaskPeriodic(RobotMode mode) {
    DBStringPrintf(DBStringPos::DB_LINE8, "w %3.2f s %3.2f i %1.2f",
                   GetWristPosition(), m_wristPositionSetpoint, m_wristInc);
    switch (m_controlMode) {
        case ControlMode::Idle:
            break;
        case ControlMode::ManualPosition:
            m_elevatorInc =
                -m_operatorJoystick->GetRawAxis(DualAction::LeftYAxis);
            m_wristInc =
                Util::signCube(-m_operatorJoystick->GetRawAxisWithDeadband(
                    DualAction::RightXAxis));
            if (GetElevatorPosition() > 78.0 &&
                GetWristPosition() < FORK_LOWER_BOUND && m_elevatorInc < 0.0) {
                m_wristPositionSetpoint = FORK_LOWER_BOUND;
                m_elevatorInc = 0.0;
            }
            else {
                m_wristPositionSetpoint +=
                    m_wristInc * MAX_WRIST_SPEED * 1.0 / 20.0;
                m_wristPositionSetpoint = Util::bound(
                    m_wristPositionSetpoint,
                    GetWristPosition() - MAX_WRIST_SPEED * 1.5 / 20.0,
                    GetWristPosition() + MAX_WRIST_SPEED * 1.5 / 20.0);
            }

            m_wrist->SetPositionStep(Util::bound(
                m_wristPositionSetpoint,
                GetWristLowerBound(GetElevatorPosition()), UPPER_WRIST_BOUND));
            m_elevator->SetPower(m_elevatorInc + ELEVATOR_FEED_FORWARD);
            break;
        case ControlMode::ManualVoltage:
            break;
        case ControlMode::Position:
            break;
        case ControlMode::switchIntaking:
            GoToIntakePosition(IntakeAssembly::IntakePosition::ground);
            if (GetElevatorPosition() < 5.0) {
                m_controlMode = ControlMode::switchStandby;
            }
            break;
        case ControlMode::switchStandby:
            if (m_wrist->IsCubeIn() ||
                m_operatorJoystick->GetRawButton(DualAction::Back)) {
                GoToIntakePosition(IntakeAssembly::IntakePosition::stow);
                m_wrist->StopIntake();
                m_intakeSignal->Reset();
                m_greyLight->SetPixelStateProcessor(m_intakeSignal);
            }
            break;
        case ControlMode::vaultStart:
            GoToIntakePosition(IntakeAssembly::IntakePosition::ground);
            m_wrist->IntakeCube(-1.0);
            m_controlMode = ControlMode::vaultStop;
            break;
        case ControlMode::vaultStop:
            if (m_wrist->IsCubeIn()) {
                StopIntake();
            }
            break;
    }
}
}
