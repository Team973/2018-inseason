/*
 * Claw.h
 *
 *  Created on: January 7, 2018
 *      Author: Kyle
 */
#pragma once

#include "WPILib.h"
#include "lib/managers/CoopTask.h"
#include "lib/logging/LogSpreadsheet.h"
#include "src/info/RobotInfo.h"

using namespace frc;

namespace frc973 {
class TaskMgr;
class LogSpreadsheet;

class Claw : public CoopTask {
public:
    Claw(TaskMgr *scheduler, LogSpreadsheet *logger, Solenoid *cubeClamp,
         Solenoid *clawKicker);

    virtual ~Claw();

    enum openState
    {
        clawOpen = true,
        clawClosed = false
    };

    enum kickState
    {
        active = true,
        kickIdle = false
    };

    enum ClawState
    {
        released,
        grabbed,
        dropOpen,
        dropClosed,
        pushOpen,
        pushClosed,
    };

    void open();
    /*
     * When called, opens the claw arms
     */
    void grab();
    /*
     * When called, closes claw arms, and
     * has all claw solenoids set to idle
     */
    void drop();
    /*
     * When called, opens claw arms to drop cube
     */
    void push();
    /*
     * When called, opens claw arms and
     * activates kicker
     */
    void kickOn();
    /*
     * When called, activates kicker
     */
    void kickOff();
    /*
     * When called, deactivates clawKicker
     */
    void TaskPeriodic(RobotMode mode);

private:
    void goToState(ClawState newState);

    TaskMgr *m_scheduler;
    Solenoid *m_cubeClamp;
    Solenoid *m_clawKicker;
    ClawState m_clawState;

    uint32_t m_stateStartTimeMs;
};
}
