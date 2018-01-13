#include "src/subsystems/Claw.h"

using namespace frc;

namespace frc973 {
Claw::Claw(TaskMgr *scheduler, LogSpreadsheet *logger,
           TalonSRX *leftRoller, TalonSRX *rightRoller,
           DigitalInput *cubeSensor)
    : m_scheduler(scheduler)
{
    this->m_scheduler->RegisterTask("Claw", this, TASK_PERIODIC);
    m_leftRoller = leftRoller;
    m_rightRoller = rightRoller;
    m_cubeSensor = cubeSensor;
}

Claw::~Claw() {
    m_scheduler->UnregisterTask(this);
}

void Claw::TaskPeriodic(RobotMode mode) {
}
}
