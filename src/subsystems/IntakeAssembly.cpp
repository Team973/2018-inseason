#include "src/subsystems/IntakeAssembly.h"
#include "WPILib.h"
#include "ctre/Phoenix.h"
#include "lib/util/WrapDash.h"

using namespace frc;

namespace frc973 {
IntakeAssembly::IntakeAssembly(TaskMgr *scheduler, LogSpreadsheet *logger,
                               Elevator *elevator, Wrist *wrist)
        : m_scheduler(scheduler)
        , m_elevator(elevator)
        , m_wrist(wrist)
        , m_controlMode(ControlMode::Idle)
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
            m_wristPositionSetpoint = Wrist::EXTENDED;
            break;
        case IntakePosition::scaleMid:
            m_elevatorPositionSetpoint = Elevator::SCALE_MID;
            m_wristPositionSetpoint = Wrist::EXTENDED;
            break;
        case IntakePosition::scaleHigh:
            m_elevatorPositionSetpoint = Elevator::SCALE_HIGH;
            m_wristPositionSetpoint = Wrist::EXTENDED;
            break;
        case IntakePosition::overBack:
            m_elevatorPositionSetpoint = Elevator::SCALE_HIGH;
            m_wristPositionSetpoint = Wrist::OVER_THE_BACK;
        default:
            break;
    }
    m_elevator->SetPosition(m_elevatorPositionSetpoint);
    m_wrist->SetPosition(m_wristPositionSetpoint);
}

void IntakeAssembly::SetElevatorManualPower(double input) {
    m_elevator->SetPower(input);
}

void IntakeAssembly::SetWristManualPower(double input) {
    m_wrist->SetPower(input);
}

void IntakeAssembly::SetPosManualInput(double elevatorInc, double wristInc) {
    m_elevatorInc = elevatorInc;
    m_wristInc = wristInc;

    double currPosition = GetWristPosition();
    m_wristPositionSetpoint += m_wristInc * MAX_WRIST_SPEED * 1.0 / 20.0;
    m_wristPositionSetpoint = Util::bound(
            m_wristPositionSetpoint,
            currPosition - MAX_WRIST_SPEED * 1.5 / 20.0,
            currPosition + MAX_WRIST_SPEED * 1.5 / 20.0);

    m_wrist->SetPositionStep(m_wristPositionSetpoint);
    m_elevator->SetPower(m_elevatorInc + ELEVATOR_FEED_FORWARD);
    m_controlMode = ControlMode::ManualPosition;
}

void IntakeAssembly::IntakeCube() {
    m_wrist->IntakeCube();
}

void IntakeAssembly::EjectCube() {
    m_wrist->EjectCube();
}

void IntakeAssembly::StopIntake() {
    m_wrist->StopIntake();
}

double IntakeAssembly::GetElevatorPosition() {
    return m_elevator->GetPosition();
}

double IntakeAssembly::GetWristPosition() {
    return m_wrist->GetPosition();
}

void IntakeAssembly::TaskPeriodic(RobotMode mode) {
    DBStringPrintf(DBStringPos::DB_LINE8, "w %3.2f s %3.2f i %1.2f",
            GetWristPosition(),
            m_wristPositionSetpoint,
            m_wristInc);

    switch (m_controlMode) {
        case ControlMode::Idle:
            break;
        case ControlMode::ManualPosition:
            break;
        case ControlMode::ManualVoltage:
            break;
        case ControlMode::Position:
            break;
    }
}

}
