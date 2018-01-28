/*
 * Elevator.h
 *
 *  Created on: January 7, 2018
 *      Author: Kyle
 */

#pragma once

#include "WPILib.h"
#include "ctre/Phoenix.h"
#include "lib/managers/CoopTask.h"
#include "lib/logging/LogSpreadsheet.h"
#include "src/info/RobotInfo.h"
#include "lib/helpers/JoystickHelper.h"

using namespace frc;

namespace frc973 {
class TaskMgr;
class LogSpreadsheet;

class Elevator : public CoopTask {
    public:
        enum Level {
            zero,
            lowGoal,
            scaleLow,
            scaleMid,
            scaleHigh
        };

        enum TalonMode {
            manual,
            motionMagic
        };

        Elevator(TaskMgr *scheduler, LogSpreadsheet *logger, ObservableJoystick *driver, TalonSRX *motor);
        virtual ~Elevator();

        /**
         * Sets Elevator Talon Control Mode
         *
         * @param mode: the control mode being set to for the talon.
         **/
        void SetControlMode(ControlMode mode, double value);
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
         * Gets Elevator Encoder Position
         *
         * @return encoder value for elevator
         **/
        double GetPosition();

        /**
         * Update function synonymous to TeleopContinuous that gets called continuously
         **/
        void TaskPeriodic(RobotMode mode);
    private:
        TaskMgr *m_scheduler;

        TalonSRX *m_elevatorMotor;

        Level m_currLevel;
        TalonMode m_talonMode;
        ObservableJoystick *m_joystick;
        LogCell *m_positionCell;
};
}
