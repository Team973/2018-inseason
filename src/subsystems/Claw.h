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

        enum EjectState{
          ejected = true,
          idle = false
        };

        void Grip();

        /**
         * Grip the cube
         **/
        void Release();

        /**
         * Releases the cube
         **/

        void Eject();

        /**
         * Eject the cube
         **/

        void TaskPeriodic(RobotMode mode);
    private:
        TaskMgr *m_scheduler;
        Solenoid *m_clawArms;
        Solenoid *m_clawKicker;
        Solenoid *m_kickerPin;
        Timer m_ejectTimer;
        EjectState m_ejectorState;
};
}
