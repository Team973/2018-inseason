/*
 * Intake.h
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

class Intake : public CoopTask {
public:
    Intake(TaskMgr *scheduler, LogSpreadsheet *logger, TalonSRX *rightRoller,
           TalonSRX *leftRoller, DigitalInput *cubeSensor, Solenoid *position);

    virtual ~Intake();

    enum class IntakeState{
      Intaking, Idle
    };

    /**
     * Starts the wheels to pull things in with the aid of beam breaker sensor
     **/
    void AutomatedPull();

    /**
     * Starts the wheels to pull things in
     **/
    void RegularPull();

    /**
     * Starts spitting whatever's in the Intake, out.
     **/
    void Eject();

    /**
     * Sets the Intake wheels to neutral, braking them.
     **/
    void Stop();

    /**
     * Checks for presense of cube
     *
     * @return Boolean if beam breaker is trigerred ot not
     **/
    bool IsCubeIn();

    void LowerIntake();

    void RaiseIntake();

    void TaskPeriodic(RobotMode mode) override;

private:
    TaskMgr *m_scheduler;
    TalonSRX *m_leftRoller;
    TalonSRX *m_rightRoller;
    DigitalInput *m_cubeSensor;
    Solenoid *m_position;
    IntakeState m_intakeState;
};
}
