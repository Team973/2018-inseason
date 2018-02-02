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
            open = true,
            idle = false
        };

        void openClaw();

        /**
         * Activates both claw arm solenoids to open the arms
         * Default position is closed
         **/

        void clawKick();

        /**
         * Activates the claw kicker solenoid
         * Pushes power cubes
         * Default state is deactivated
         **/

        void runKickerPin();

        /**
         * Enables the kicker print
         * Default state is disabled
         **/

        void TaskPeriodic(RobotMode mode);
    private:
        TaskMgr *m_scheduler;
        Solenoid *m_clawArms;
        Solenoid *m_clawKicker;
        Solenoid *m_kickerPin;
        Timer m_openTimer;
        openState m_openerState;

};
}
