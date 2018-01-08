#include "src/subsystems/Elevator.h"

using namespace frc;

namespace frc973 {
    Elevator::Elevator(TaskMgr *scheduler, LogSpreadsheet *logger)
    : m_scheduler(scheduler)
    {
    }

    virtual Elevator::~Elevator() {
        m_scheduler->UnregisterTask(this);
    }

    void Elevator::TaskPeriodic(RobotMode mode) {
    }
}
