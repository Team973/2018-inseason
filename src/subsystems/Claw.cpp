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
    /* Timer m_ejectTimer();
    m_ejectorState = idle; */
}

Claw::~Claw() {
    m_scheduler->UnregisterTask(this);
}

void Claw::Eject() {

  /*
  m_ejector->Set(Claw::EjectState::ejected);
  m_ejectTimer.Start();
  m_ejectorState = ejected;
  */
}

void Claw::Grip() {
  /*
  m_leftArm->Set(true);
  m_rightArm->Set(true);
  */
}

void Claw::Release() {
  /*
  m_leftArm->Set(false);
  m_rightArm->Set(false);
  */
}
void Claw::TaskPeriodic(RobotMode mode) {
  /* if (m_ejectorState == ejected && m_ejectTimer.Get()>= 0.5){
    m_ejectorState = idle;
    m_ejector->Set(Claw::EjectState::idle);
    m_ejectTimer.Stop();
    m_ejectTimer.Reset();
    */
  }
}
