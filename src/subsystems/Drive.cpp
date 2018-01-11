#include "src/subsystems/Drive.h"

using namespace frc;

namespace frc973 {
    Drive::Drive(TaskMgr *scheduler, LogSpreadsheet *logger)
    : m_scheduler(scheduler)
    {
        this->m_scheduler->RegisterTask("Drive", this, TASK_PERIODIC);
    }

    virtual Drive::~Drive() {
        m_scheduler->UnregisterTask(this);
    }

    void Drive::TaskPeriodic(RobotMode mode) {
    }
}
