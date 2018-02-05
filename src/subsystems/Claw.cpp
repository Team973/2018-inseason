#include "src/subsystems/Claw.h"

using namespace frc;

namespace frc973 {
Claw::Claw(TaskMgr *scheduler, LogSpreadsheet *logger, Solenoid *clawArms,
           Solenoid *clawKicker, Solenoid *kickerPin)
        : m_scheduler(scheduler)
        , m_clawArms(clawArms)
        , m_clawKicker(clawKicker)
        , m_kickerPin(kickerPin)
        , m_clawState(Claw::ClawState::grabbed) {
    this->m_scheduler->RegisterTask("Claw", this, TASK_PERIODIC);
    goToState(grabbed);
}

Claw::~Claw() {
    m_scheduler->UnregisterTask(this);
}

void Claw::open() {
    goToState(released);
}

void Claw::grab() {
    goToState(grabbed);
}

void Claw::drop() {
    goToState(dropOpen);
}

void Claw::push() {
    goToState(pushOpen);
}

void Claw::fire() {
    goToState(kickHold);
}

void Claw::TaskPeriodic(RobotMode mode) {
    switch (m_clawState) {
        case ClawState::released:
            break;
        case ClawState::grabbed:
            break;
        case ClawState::dropOpen:
            if (GetMsecTime() - m_stateStartTimeMs > 100) {
                goToState(dropClosed);
            }
            break;
        case ClawState::dropClosed:
            goToState(grabbed);
            break;
        case ClawState::pushOpen:
            if (GetMsecTime() - m_stateStartTimeMs > 100) {
                goToState(pushClosed);
            }
            break;
        case ClawState::pushClosed:
            goToState(grabbed);
            break;
        case ClawState::kickHold:
            if (GetMsecTime() - m_stateStartTimeMs > 50) {
                goToState(kickPreFire);
            }
            break;
        case ClawState::kickPreFire:
            if (GetMsecTime() - m_stateStartTimeMs > 50) {
                goToState(kickRelease);
            }
            break;
        case ClawState::kickRelease:
            goToState(grabbed);
            break;
    }
}
void Claw::goToState(ClawState newState) {
    m_stateStartTimeMs = GetMsecTime();
    m_clawState = newState;
    switch (m_clawState) {
        case ClawState::released:
            m_clawArms->Set(clawOpen);
            m_clawKicker->Set(kickIdle);
            m_kickerPin->Set(pinIdle);
            break;
        case ClawState::grabbed:
            m_clawArms->Set(clawClosed);
            m_clawKicker->Set(kickIdle);
            m_kickerPin->Set(pinIdle);
            break;
        case ClawState::dropOpen:
            m_clawArms->Set(clawOpen);
            m_clawKicker->Set(kickIdle);
            m_kickerPin->Set(pinIdle);
            break;
        case ClawState::dropClosed:
            m_clawArms->Set(clawClosed);
            m_clawKicker->Set(kickIdle);
            m_kickerPin->Set(pinIdle);
            break;
        case ClawState::pushOpen:
            m_clawArms->Set(clawOpen);
            m_clawKicker->Set(active);
            m_kickerPin->Set(pinIdle);
            break;
        case ClawState::pushClosed:
            m_clawArms->Set(clawClosed);
            m_clawKicker->Set(kickIdle);
            m_kickerPin->Set(pinIdle);
            break;
        case ClawState::kickHold:
            m_clawArms->Set(clawClosed);
            m_clawKicker->Set(kickIdle);
            m_kickerPin->Set(pinActive);
            break;
        case ClawState::kickPreFire:
            m_clawArms->Set(clawClosed);
            m_clawKicker->Set(active);
            m_kickerPin->Set(pinActive);
            break;
        case ClawState::kickRelease:
            m_clawArms->Set(clawOpen);
            m_clawKicker->Set(active);
            m_kickerPin->Set(pinIdle);
            break;
    }
}
}
