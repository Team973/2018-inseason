/*
 * Claw.h
 *
 *  Created on: January 7, 2018
 *      Author: Kyle
 */
#pragma once

#include "WPILib.h"
#include "Phoenix.h"
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
             TalonSRX *rightRoller, TalonSRX *leftRoller,
             DigitalInput *cubeSensor);

        virtual ~Claw();


        /**
         * Starts the wheels to pull things in
         **/
        void Intake();

        /**
         * Starts spitting whatever's in the claw, out.
         **/
        void Eject();

        /**
         * Sets the claw wheels to neutral, braking them.
         **/
        void Stop();

        /**
          * Checks for presense of cube
          *
          * @return Boolean if beam breaker is trigerred ot not
          **/
        bool IsCubeIn();


        void TaskPeriodic(RobotMode mode);
    private:
        TaskMgr *m_scheduler;
        TalonSRX *m_leftRoller;
        TalonSRX *m_rightRoller;
        DigitalInput *m_cubeSensor;
};
}
