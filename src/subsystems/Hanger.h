/*
 * Hanger.h
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
#include "src/subsystems/Drive.h"
#include "src/subsystems/Elevator.h"

using namespace frc;

namespace frc973 {
class TaskMgr;
class LogSpreadsheet;

class Hanger : public CoopTask {
public:
    Hanger(TaskMgr *scheduler, LogSpreadsheet *logger, Drive *drive,
           Elevator *elevator, Solenoid *hangerpto);
    virtual ~Hanger();

    void EngagePTO();
    /**
     * Engages the hanger PTO
     **/
    void DisengagePTO();
    /**
     * Disengages the hanger PTO
     **/
    void TaskPeriodic(RobotMode mode);

private:
    TaskMgr *m_scheduler;
    LogSpreadsheet *m_logger;
    Drive *m_drive;
    Elevator *m_elevator;
    Solenoid *m_hangerpto;
};
}
