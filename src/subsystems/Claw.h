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
        kickIdle = false,
    };

    enum ClawState
    {
        released,
        grabbed,
        dropOpen,
        dropClosed,
        pushOpen,
        pushClosed,
        preLaunch,
        launch,
        launchReset,
        kickManual,
        clawManual,
        manual
    };

    /*
     * When called, opens the claw arms
     */
    void open();

    /*
     * When called, closes claw arms, and
     * has all claw solenoids set to idle
     */
    void grab();

    /*
     * When called, opens claw arms to drop cube
     */
    void drop();

    /*
     * When called, opens claw arms and
     * activates kicker
     */
    void push();

    /*
     * When called, launches cube
     */
    void cubeLaunch();

    /*
     * When called, activates kicker
     */
    void manualKickOn();

    /*
     * When called, sets kick to manual
     */
    void manualKickOff();

    /*
     * When called, sets claw to open state
     */
    void manualClawOn();

    /*
     * When called, sets claw to manual
     */
    void manualClawOff();

    /*
     * Activates the kicker
     */
    void kickOn();

    /*
     * Deactivates the kicker
     */
    void kickOff();

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
