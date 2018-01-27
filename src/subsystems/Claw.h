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
             Solenoid *rightArm, Solenoid *leftArm, Solenoid *ejector);

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
        Solenoid *m_leftArm;
        Solenoid *m_rightArm;
        Solenoid *m_ejector;
        Timer m_ejectTimer;
        EjectState m_ejectorState;
};
}
