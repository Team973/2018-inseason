#include "src/subsystems/Claw.h"

using namespace frc;

namespace frc973 {
Claw::Claw(TaskMgr *scheduler, LogSpreadsheet *logger)
        : m_scheduler(scheduler) {
    this->m_scheduler->RegisterTask("Claw", this, TASK_PERIODIC);
}

Claw::~Claw() {
    m_scheduler->UnregisterTask(this);
}

void Claw::TaskPeriodic(RobotMode mode) {
}
}
