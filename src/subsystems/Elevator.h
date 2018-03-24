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
#include "lib/util/Util.h"

using namespace frc;

namespace frc973 {
class TaskMgr;
class LogSpreadsheet;

class Elevator : public CoopTask {
public:
    enum ElevatorState
    {
        manualVoltage,
        manualPosition,
        motionMagic
    };

    static constexpr double GROUND = 0.0;
    static constexpr double VAULT = 4.5;
    static constexpr double LOW_GOAL = 30.0;
    static constexpr double HANGING = 55.0;
    static constexpr double SCALE_LOW = 58.0;
    static constexpr double SCALE_MID = 70.0;
    static constexpr double SCALE_HIGH = 80.5;

    Elevator(TaskMgr *scheduler, LogSpreadsheet *logger,
             TalonSRX *elevatorMotor);
    virtual ~Elevator();

    /**
     * Sets Elevator Position using Motion Magic
     *
     * @param position: the position goal
     **/
    void SetPosition(double position);

    // Uses Position PID
    void SetManualInput(double input);
    /**
     * Sets Elevator Power
     *
     * @param power: power being sent to the motor from -1.0 to 1.0
     **/
    void SetPower(double power);

    /**
     * @return: returns current elevator position in sensor units
     **/
    float GetPosition();

    void ZeroPosition();

    void EnableBrakeMode();
    void EnableCoastMode();

    /**
     * Update function synonymous to TeleopContinuous that gets called
     *continuously
     **/
    void TaskPeriodic(RobotMode mode);

private:
    TaskMgr *m_scheduler;

    TalonSRX *m_elevatorMotor;

    double m_position;
    double m_prevElevatorSetpoint;
    double m_elevatorPositionDelta;
    uint32_t m_zeroingTime;
    ElevatorState m_elevatorState;
    LogCell *m_positionCell;
};
}
