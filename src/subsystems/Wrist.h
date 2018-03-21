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

class Wrist : public CoopTask {
public:
    static constexpr double GROUND = 0.0;
    static constexpr double VAULT = 4.5;
    static constexpr double LOW_GOAL = 30.0;
    static constexpr double HANGING = 55.0;
    static constexpr double SCALE_LOW = 64.0;
    static constexpr double SCALE_MID = 70.0;
    static constexpr double SCALE_HIGH = 78.0;

    Wrist(TaskMgr *scheduler, LogSpreadsheet *logger, TalonSRX *wristMotor);
    virtual ~Wrist();

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
     * @return: returns current elevator position in sensor units
     **/
    float GetPosition();

    void ZeroPosition();

    /**
     * Update function synonymous to TeleopContinuous that gets called
     *continuously
     **/
    void TaskPeriodic(RobotMode mode);

private:
    TaskMgr *m_scheduler;
    TalonSRX *m_wristMotor;

    double m_position;
    uint32_t m_zeroingTime;
    LogCell *m_positionCell;
};
}
