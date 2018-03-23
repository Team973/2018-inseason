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

void IntakeAssembly::GoToStow() {
    m_elevator->SetPosition(Elevator::GROUND);
}

void IntakeAssembly::TaskPeriodic(RobotMode mode) {
}
}
