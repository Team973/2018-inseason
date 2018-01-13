/*
 * Drive.h
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
#include "lib/bases/DriveBase.h"

using namespace frc;

namespace frc973 {
class TaskMgr;
class LogSpreadsheet;

class Drive : public CoopTask {
    public:
        Drive(TaskMgr *scheduler, LogSpreadsheet *logger, TalonSRX *leftTalon, TalonSRX *rightTalon, VictorSPX *slaveLeftone,
              VictorSPX *slaveLefttwo, VictorSPX *slaveRightone, VictorSPX *slaveRighttwo, ADXRS450_Gyro *driveGyro);
        virtual ~Drive();

        void TaskPeriodic(RobotMode mode);
    private:
        TaskMgr *m_scheduler;
        TalonSRX *m_leftTalon, *m_rightTalon;
        VictorSPX *m_slaveLeftone, *m_slaveLefttwo, *m_slaveRightone, *m_slaveRighttwo;
        ADXRS450_Gyro *m_driveGyro;
};
}
