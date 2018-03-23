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

void IntakeAssembly::GoToIntakePosition() {
    switch (m_intakePosition) {
        case IntakePosition::stow:
            m_elevatorPositionSetpoint = Elevator::GROUND;
            m_wristPositionSetpoint = Wrist::STOW;
            break;
        case IntakePosition::vault:
            m_elevatorPositionSetpoint = Elevator::VAULT;
            m_wristPositionSetpoint = Wrist::STOW;
            break;
        case IntakePosition::lowGoal:
            m_elevatorPositionSetpoint = Elevator::LOW_GOAL;
            m_wristPositionSetpoint = Wrist::STOW;
            break;
        case IntakePosition::scaleLow:
            m_elevatorPositionSetpoint = Elevator::SCALE_LOW;
            m_wristPositionSetpoint = Wrist::STOW;
            break;
        case IntakePosition::scaleMid:
            m_elevatorPositionSetpoint = Elevator::SCALE_MID;
            m_wristPositionSetpoint = Wrist::STOW;
            break;
        case IntakePosition::scaleHigh:
            m_elevatorPositionSetpoint = Elevator::SCALE_HIGH;
            m_wristPositionSetpoint = Wrist::STOW;
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

void IntakeAssembly::TaskPeriodic(RobotMode mode) {
}
}
