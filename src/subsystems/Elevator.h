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
#include "src/RobotInfo.h"

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

        void SetControlMode(ControlMode mode);
        void SetPosition(double position);
        void SetPower(double power);
        void SetMotionMagic(double position);
        void SetLevel(Level level);

        void Reset();

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
