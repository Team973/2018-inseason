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
    static constexpr double STOW = -35.0;
    static constexpr double SCALE = 20.0;
    static constexpr double EXTENDED = 90.0;
    static constexpr double OVER_THE_BACK = -80.0;

    static constexpr double WRIST_DEGREES_PER_CLICK = 360.0 / 4096.0;

    static const int WRIST_REVERSE_SOFT_LIMIT = -80.0;
    static const int WRIST_FORWARD_SOFT_LIMIT = 90.0;

    Wrist(TaskMgr *scheduler, LogSpreadsheet *logger, TalonSRX *wristMotor);
    virtual ~Wrist();

    /**
     * Sets Wrist Position using Motion Magic
     *
     * @param position: the position goal
     **/
    void SetPosition(double position);
    void SetPositionStep(double position);

    /**
     * Sets Elevator Power
     *
     * @param power: power being sent to the motor from -1.0 to 1.0
     **/
    void SetPower(double power);

    /**
     * @return: returns current elevator position in sensor units
     **/
    float GetPosition() const;

    void ZeroPosition();

    void TaskPeriodic(RobotMode mode);

    TalonSRX *m_wristMotor;

private:
    /*
     * Convert a number from degrees to native encoder units and vise versa
     */
    double DegreesToNativeUnits(double degrees) const;
    double NativeUnitsToDegrees(double nativeUnits) const;

    enum class WristState
    {
        manualVoltage,
        motionMagic,
        manualPosition
    };

    TaskMgr *m_scheduler;

    double m_position;
    double m_prevWristSetpoint;
    double m_wristPositionDelta;
    uint32_t m_zeroingTime;
    bool m_prevLimSwitchState;
};
}
