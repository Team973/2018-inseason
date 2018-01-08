#include "src/subsystems/Claw.h"

using namespace frc;

namespace frc973 {
    Claw::Claw(TaskMgr *scheduler, LogSpreadsheet *logger)
    : m_scheduler(scheduler)
    {
    }

    virtual Claw::~Claw() {
        m_scheduler->UnregisterTask(this);
    }

    void Claw::TaskPeriodic(RobotMode mode) {
    }
}
