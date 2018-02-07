/*
 * Elevator.h
 *
 *  Created on: January 7, 2018
 *      Author: Kyle
 */

#pragma once

#include "WPILib.h"
#include "ctre/Phoenix.h"
#include "lib/managers/CoopTask.h"
#include "lib/logging/LogSpreadsheet.h"
#include "src/info/RobotInfo.h"
#include "lib/helpers/JoystickHelper.h"

using namespace frc;

namespace frc973 {
class TaskMgr;
class LogSpreadsheet;

class Elevator : public CoopTask {
public:
    enum ElevatorState
    {
        manual,
        zeroing,
        position,
        goDown,
        stop
    };

    static constexpr double GROUND = 0.1;
    static constexpr double VAULT = 3.0;
    static constexpr double LOW_GOAL = 25.0;
    static constexpr double SCALE_LOW = 50.0;
    static constexpr double SCALE_MID = 60.0;
    static constexpr double SCALE_HIGH = 85.0;

    Elevator(TaskMgr *scheduler, LogSpreadsheet *logger, TalonSRX *motor);
    virtual ~Elevator();

    /**
     * Sets Elevator Position
     *
     * @param position: the position goal
     **/
    void SetPosition(double position);

    /**
     * Sets Elevator Power
     *
     * @param power: power being sent to the motor from -1.0 to 1.0
     **/
    void SetPower(double power);

    /**
     * Resets elevator subsystem by setting position to zero
     *  and setting control modes to % output
     **/
    void Reset();

    /**
     * @return: returns current elevator position in sensor units
     **/
    float GetPosition();

    /**
     * Update function synonymous to TeleopContinuous that gets called
     *continuously
     **/
    void TaskPeriodic(RobotMode mode);

private:
    TaskMgr *m_scheduler;

    TalonSRX *m_elevatorMotor;

    double m_position;
    ElevatorState m_elevatorState;
    LogCell *m_positionCell;
};
}
