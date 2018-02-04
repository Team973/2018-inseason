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
        Claw(TaskMgr *scheduler, LogSpreadsheet *logger,
             Solenoid *clawArms, Solenoid *clawKicker, Solenoid *kickerPin);

        virtual ~Claw();

        /**
         * Starts the wheels to pull things in
         **/

        enum openState {
            clawOpen = true,
            clawClosed = false
        };

        enum kickState {
            active = true,
            kickIdle = false
        };

        enum kickPinState {

            /*
            * Activating the pin holds the kicker in place
            */

            pinActive = true,
            pinIdle = false
        };

        enum ClawState {
            released,
            grabbed,
            dropOpen,
            dropClosed,
            pushOpen,
            pushClosed,
            kickHold,
            kickPreFire,
            kickRelease,
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
        void fire();
        /*
        * When called, sets cube to be launched by the
        * kicker aided by the kicker pin
        */
        void TaskPeriodic(RobotMode mode);
    private:

        void goToState(ClawState newState);


        TaskMgr *m_scheduler;
        Solenoid *m_clawArms;
        Solenoid *m_clawKicker;
        Solenoid *m_kickerPin;
        ClawState m_clawState;

        uint32_t m_stateStartTimeMs;


};
}
