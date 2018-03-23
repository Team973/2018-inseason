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
        , m_elevatorPosition(0.0)
        , m_wristPosition(0.0) {
    this->m_scheduler->RegisterTask("IntakeAssembly", this, TASK_PERIODIC);
}

IntakeAssembly::~IntakeAssembly() {
    m_scheduler->UnregisterTask(this);
}

void IntakeAssembly::GoToIntakePosition() {
    switch (m_intakePosition) {
        case IntakePosition::stow:
            m_elevatorPosition = Elevator::GROUND;
            m_wristPosition = Wrist::STOW;
            break;
        case IntakePosition::vault:
            m_elevatorPosition = Elevator::VAULT;
            m_wristPosition = Wrist::STOW;
            break;
        case IntakePosition::lowGoal:
            m_elevatorPosition = Elevator::LOW_GOAL;
            m_wristPosition = Wrist::STOW;
            break;
        case IntakePosition::scaleLow:
            m_elevatorPosition = Elevator::SCALE_LOW;
            m_wristPosition = Wrist::STOW;
            break;
        case IntakePosition::scaleMid:
            m_elevatorPosition = Elevator::SCALE_MID;
            m_wristPosition = Wrist::STOW;
            break;
        case IntakePosition::scaleHigh:
            m_elevatorPosition = Elevator::SCALE_HIGH;
            m_wristPosition = Wrist::STOW;
            break;
        case IntakePosition::overBack:
            m_elevatorPosition = Elevator::SCALE_HIGH;
            m_wristPosition = Wrist::OVER_THE_BACK;
        default:
            break;
    }
    m_elevator->SetPosition(m_elevatorPosition);
    m_wrist->SetPosition(m_wristPosition);
}

void IntakeAssembly::TaskPeriodic(RobotMode mode) {
}
}
