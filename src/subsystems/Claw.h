/*
 * Claw.h
 *
 *  Created on: January 7, 2018
 *      Author: Kyle
 */
#pragma once

#include "WPILib.h"
#include "lib/managers/CoopTask.h"
#include "lib/logging/LogSpreadsheet.h"
#include "src/info/RobotInfo.h"

using namespace frc;

namespace frc973 {
class TaskMgr;
class LogSpreadsheet;

class Claw : public CoopTask {
public:
    Claw(TaskMgr *scheduler, LogSpreadsheet *logger, Solenoid *cubeClamp);

    virtual ~Claw();

    enum openState
    {
        clawOpen = true,
        clawClosed = false
    };

    /*
     * When called, opens the claw arms
     */
    void open();

    /*
     * When called, closes claw arms
     */
    void grab();

    void TaskPeriodic(RobotMode mode);

private:
    TaskMgr *m_scheduler;
    Solenoid *m_cubeClamp;
};
}
