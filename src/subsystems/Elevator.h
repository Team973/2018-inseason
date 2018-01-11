/*
 * Elevator.h
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

class Elevator : public CoopTask {
    public:
        enum Level {
            zero,
            vault,
            switch,
            scaleLow,
            scaleMid,
            scaleHigh,
            manual
        };

        Elevator(TaskMgr *scheduler, LogSpreadsheet *logger);
        virtual ~Elevator();

        /**
         * Sets Elevator Talon Control Mode
         *
         * @param mode: the control mode being set to for the talon.
         **/
        void SetControlMode(ControlMode mode);
        /**
         * Sets Elevator Position
         *
         * @param position: the position goal
         **/
        void SetPosition(double position);
        /**
         * Sets Elevator Power
         *
         * @param power: power being sent to the motor from -1.0 to 1.0
         **/
        void SetPower(double power);
        /**
         * Sets Elevator Talon Control Mode to Motion Magic and uses Motion profiling
         * to set position goal
         *
         * @param position: the position goal of the elevator
         **/
        void SetMotionMagic(double position);

        /**
         * Sets Elevator Level
         *
         * @param level: the level the elevator should be in (refer to enum above for choices)
         **/
        void SetLevel(Level level);

        /**
         * Resets elevator subsystem by setting position to zero
         *  and setting control modes to % output
         **/
        void Reset();

        /**
         * Update function synonymous to TeleopContinuous that gets called continuously
         **/
        void TaskPeriodic(RobotMode mode);
    private:
        TaskMgr *m_scheduler;

        CANTalon *m_elevatorMotor;

        double m_position;
        Level m_currLevel;
        motorcontrol::ControlMode m_talonMode;

        LogCell *m_positionCell;
}
}
