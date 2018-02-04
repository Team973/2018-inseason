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
    m_openerState = idle;
    Timer m_kickTimer();
    m_kickerState = kickIdle;
    Timer m_kickPinState();
    m_kickPinState = pinIdle;
}

Claw::~Claw() {
    m_scheduler->UnregisterTask(this);
}

void Claw::openClaw() {
    m_clawArms->Set(Claw::openState::open);
    m_openTimer.Start();
    m_openerState = open;
}

void Claw::clawKick() {
    m_clawKicker->Set(Claw::kickState::active);
    m_kickTimer.Start();
    m_kickerState = active;
}

void Claw::runKickerPin() {
    m_kickerPin->Set(Claw::kickPinState::pinActive);
    m_pinTimer.Start();
    m_kickPinState = pinActive;
}
void Claw::TaskPeriodic(RobotMode mode) {
    if(m_openerState == open && m_openTimer.Get()>= 0.5) {
        m_openerState = idle;
        m_clawArms->Set(Claw::openState::idle);
        m_openTimer.Stop();
        m_openTimer.Reset();
    }
    if(m_kickerState == active && m_kickTimer.Get()>= 0.5) {
        m_kickerState = kickIdle;
        m_clawKicker->Set(Claw::kickerState::kickIdle);
        m_kickTimer.Stop();
        m_kickTimer.Reset();
    }
    if(m_kickPinState == pinActive && m_pinTimer.Get()>= 0.5) {
        m_kickPinState = pinIdle;
        m_kickerPin->Set(Claw::kickPinState::pinIdle);
        m_pinTimer.Stop();
        m_pinTimer.Reset();
    }

  }
}
