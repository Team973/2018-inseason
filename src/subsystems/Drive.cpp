#include "src/subsystems/Drive.h"

using namespace frc;

namespace frc973 {
    Drive::Drive(TaskMgr *scheduler, LogSpreadsheet *logger)
    : m_scheduler(scheduler)
    {
    }

    virtual Drive::~Drive() {
        m_scheduler->UnregisterTask(this);
    }

    void Drive::TaskPeriodic(RobotMode mode) {
    }
}
