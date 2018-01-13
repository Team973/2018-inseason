#include "src/subsystems/Hanger.h"

using namespace frc;

namespace frc973 {
Hanger::Hanger(TaskMgr *scheduler, LogSpreadsheet *logger)
: m_scheduler(scheduler)
{
    this->m_scheduler->RegisterTask("Hanger", this, TASK_PERIODIC);
}

Hanger::~Hanger() {
    m_scheduler->UnregisterTask(this);
}

void Hanger::TaskPeriodic(RobotMode mode) {
}
}
