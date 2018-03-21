#include "src/subsystems/Claw.h"
#include "lib/util/WrapDash.h"

using namespace frc;

namespace frc973 {
Claw::Claw(TaskMgr *scheduler, LogSpreadsheet *logger, Solenoid *cubeClamp)
        : m_scheduler(scheduler), m_cubeClamp(cubeClamp) {
    this->m_scheduler->RegisterTask("Claw", this, TASK_PERIODIC);
}

Claw::~Claw() {
    m_scheduler->UnregisterTask(this);
}

void Claw::open() {
    m_cubeClamp->Set(clawOpen);
}

void Claw::grab() {
    m_cubeClamp->Set(clawClosed);
}

void Claw::TaskPeriodic(RobotMode mode) {
}
}
