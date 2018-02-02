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
    Claw(TaskMgr *scheduler, LogSpreadsheet *logger, TalonSRX *rightRoller,
         TalonSRX *leftRoller, DigitalInput *cubeSensor, Solenoid *clawArms,
         Solenoid *clawKicker, Solenoid *kickerPin);
    virtual ~Claw();

    void Intake();
    void Eject();
    void Stop();

    void TaskPeriodic(RobotMode mode);

private:
    TaskMgr *m_scheduler;
    TalonSRX *m_leftRoller;
    TalonSRX *m_rightRoller;
    DigitalInput *m_cubeSensor;
    Solenoid *m_clawArms;
    Solenoid *m_clawKicker;
    Solenoid *m_kickerPin;
};
}
