#include "src/subsystems/Claw.h"

using namespace frc;

namespace frc973 {
Claw::Claw(TaskMgr *scheduler, LogSpreadsheet *logger, Solenoid *cubeClamp,
           Solenoid *clawKicker)
        : m_scheduler(scheduler)
        , m_cubeClamp(cubeClamp)
        , m_clawKicker(clawKicker)
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

void Claw::kickOn() {
    m_clawKicker->Set(active);
}

void Claw::kickOff() {
    m_clawKicker->Set(kickIdle);
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
    }
}
void Claw::goToState(ClawState newState) {
    m_stateStartTimeMs = GetMsecTime();
    m_clawState = newState;
    switch (m_clawState) {
        case ClawState::released:
            m_cubeClamp->Set(clawOpen);
            m_clawKicker->Set(kickIdle);
            break;
        case ClawState::grabbed:
            m_cubeClamp->Set(clawClosed);
            m_clawKicker->Set(kickIdle);
            break;
        case ClawState::dropOpen:
            m_cubeClamp->Set(clawOpen);
            m_clawKicker->Set(kickIdle);
            break;
        case ClawState::dropClosed:
            m_cubeClamp->Set(clawClosed);
            m_clawKicker->Set(kickIdle);
            break;
        case ClawState::pushOpen:
            m_cubeClamp->Set(clawOpen);
            m_clawKicker->Set(active);
            break;
        case ClawState::pushClosed:
            m_cubeClamp->Set(clawClosed);
            m_clawKicker->Set(kickIdle);
            break;
    }
}
}
