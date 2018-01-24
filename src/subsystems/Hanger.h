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
           Elevator *elevator, Solenoid *hangerpto, TalonSRX *forkliftTalon,
           VictorSPX *forkliftVictor);
    virtual ~Hanger();

    void EngagePTO();
    /**
     * Engages the hanger PTO, runs drive + elevator motors
     **/
    void DisengagePTO();
    /**
     * Disengages the hanger PTO, stops drive + elevator motors
     **/
    void ForkliftForwardpower();
    /**
     * Sets all forklift motors forward at %100 speed
     **/
    void ForkliftReversepower();
    /**
     * Sets all forklift motors in reverse at %100 speed
     **/
    void TaskPeriodic(RobotMode mode);

private:
    TaskMgr *m_scheduler;
    LogSpreadsheet *m_logger;
    Drive *m_drive;
    Elevator *m_elevator;
    Solenoid *m_hangerpto;
    TalonSRX *m_forkliftTalon;
    VictorSPX *m_forkliftVictor;
};
}
