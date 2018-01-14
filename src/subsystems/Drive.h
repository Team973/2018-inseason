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
        Drive(TaskMgr *scheduler, LogSpreadsheet *logger, TalonSRX *leftDriveTalonA, VictorSPX *leftDriveVictorB, VictorSPX *leftDriveVictorC, TalonSRX *rightDriveTalonA, VictorSPX *rightDriveVictorB, VictorSPX *rightDriveVictorC, ADXRS450_Gyro *driveGyro);
        virtual ~Drive();

        void TaskPeriodic(RobotMode mode);
    private:
        TaskMgr *m_scheduler;
        LogSpreadsheet *m_logger;

        TalonSRX *m_leftDriveTalonA;
        VictorSPX *m_leftDriveVictorB;
        VictorSPX *m_leftDriveVictorC;
        TalonSRX *m_rightDriveTalonA;
        VictorSPX *m_rightDriveVictorB;
        VictorSPX *m_rightDriveVictorC;

        ADXRS450_Gyro *m_driveGyro;
};
}
