/*
 * Drive.h
 *
 *  Created on: January 7, 2018
 *      Author: Kyle
 */
#pragma once

#include "WPILib.h"
#include "Phoenix.h"
#include "ADXRS450_Gyro.h"
#include "lib/managers/CoopTask.h"
#include "lib/logging/LogSpreadsheet.h"
#include "src/info/RobotInfo.h"
#include "lib/bases/DriveBase.h"

using namespace frc;
using namespace ctre;

namespace frc973 {
class TaskMgr;
class LogSpreadsheet;

class Drive : public CoopTask {
    public:
        Drive(TaskMgr *scheduler, LogSpreadsheet *logger, phoenix::motorcontrol::can::TalonSRX *leftTalonA, phoenix::motorcontrol::can::VictorSPX *leftVictorB, phoenix::motorcontrol::can::VictorSPX *leftVictorC, phoenix::motorcontrol::can::TalonSRX *rightTalonA, phoenix::motorcontrol::can::VictorSPX *rightVictorB, phoenix::motorcontrol::can::VictorSPX *rightVictorC, ADXRS450_Gyro *driveGyro);
        virtual ~Drive();

        void TaskPeriodic(RobotMode mode);
    private:
        TaskMgr *m_scheduler;
        LogSpreadsheet *m_logger;

        phoenix::motorcontrol::can::TalonSRX *m_leftTalonA;
        phoenix::motorcontrol::can::VictorSPX *m_leftVictorB;
        phoenix::motorcontrol::can::VictorSPX *m_leftVictorC;
        phoenix::motorcontrol::can::TalonSRX *m_rightTalonA;
        phoenix::motorcontrol::can::VictorSPX *m_rightVictorB;
        phoenix::motorcontrol::can::VictorSPX *m_rightVictorC;

        ADXRS450_Gyro *m_driveGyro;
};
}
