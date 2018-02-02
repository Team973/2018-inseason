#include "src/subsystems/Claw.h"

using namespace frc;

namespace frc973 {
Claw::Claw(TaskMgr *scheduler, LogSpreadsheet *logger,
           Solenoid *clawArms, Solenoid *clawKicker, Solenoid *kickerPin)
    : m_scheduler(scheduler)
    , m_clawArms(clawArms)
    , m_clawKicker(clawKicker)
    , m_kickerPin(kickerPin)
{
    this->m_scheduler->RegisterTask("Claw", this, TASK_PERIODIC);
    Timer m_openTimer();
    m_openState = idle;
}

Claw::~Claw() {
    m_scheduler->UnregisterTask(this);
}

void Claw::openClaw() {
    m_clawArms->Set(Claw::OpenState::Open);
    m_openTimer.Start();
    m_openerState = open;
}

void Claw::clawKick() {

}

void Claw::runKickerPin() {

}
void Claw::TaskPeriodic(RobotMode mode) {
    if(m_openerState == open && m_openTimer.Get()>= 0.5) {
        m_openerState = idle;
        m_opener->set(Claw::EjectState::idle);
        m_openTimer.Stop();
        m_openTimer.Reset();
    }
  }
}
