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
            scale,
            manual
        };

        Elevator(TaskMgr *scheduler, LogSpreadsheet *logger);
        virtual ~Elevator();

        void SetPosition(double position);
        void SetPower(double power);

        void Reset();

        void TaskPeriodic(RobotMode mode);
    private:
        TaskMgr *m_scheduler;

        CANTalon *m_elevatorMotor;

        double m_position;
        Level m_currLevel;

}
}
