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
        , m_elevatorPositionSetpoint(0.0)
        , m_wristPositionSetpoint(0.0) {
    this->m_scheduler->RegisterTask("IntakeAssembly", this, TASK_PERIODIC);
}

IntakeAssembly::~IntakeAssembly() {
    m_scheduler->UnregisterTask(this);
}

void IntakeAssembly::GoToIntakePosition(IntakePosition intakePosition) {
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

double IntakeAssembly::GetElevatorPosition() {
    return m_elevator->GetPosition();
}

double IntakeAssembly::GetWristPosition() {
    return m_wrist->GetPosition();
}

void IntakeAssembly::TaskPeriodic(RobotMode mode) {
}
}
