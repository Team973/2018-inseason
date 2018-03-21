/*
 * Claw.h
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

class Claw : public CoopTask {
public:
    Claw(TaskMgr *scheduler, LogSpreadsheet *logger, DigitalInput *cubeSensor,
         Solenoid *cubeClamp, TalonSRX *leftRoller, TalonSRX *rightRoller);

    virtual ~Claw();

    enum openState
    {
        clawOpen = true,
        clawClosed = false
    };

    /*
     * When called, opens the claw arms
     */
    void OpenClaw();

    /*
     * When called, closes claw arms
     */
    void CloseClaw();

    void IntakeCube();
    void EjectCube();

    bool IsCubeIn();

    void TaskPeriodic(RobotMode mode);

private:
    TaskMgr *m_scheduler;
    DigitalInput *m_cubeSensor;
    Solenoid *m_cubeClamp;

    TalonSRX *m_leftRoller;
    TalonSRX *m_rightRoller;
};
}
