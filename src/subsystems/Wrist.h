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

/**
 * Wrist subsystem.
 */
class Wrist : public CoopTask {
public:
    static constexpr double STOW = -35.0;          /**< The stow preset. */
    static constexpr double SCALE = 20.0;          /**< The scale preset. */
    static constexpr double EXTENDED = 90.0;       /**< The extended preset. */
    static constexpr double OVER_THE_BACK = -80.0; /**< The overhead preset. */

    static constexpr double WRIST_DEGREES_PER_CLICK =
        360.0 / 4096.0; /**< The encoder's degrees/click. */

    static const int WRIST_REVERSE_SOFT_LIMIT =
        -80.0; /**< The max backwards limit. */
    static const int WRIST_FORWARD_SOFT_LIMIT =
        90.0; /**< The max forwards limit. */

    /**
     * Construct a wrist.
     * @param scheduler TaskMgr object.
     * @param logger LogSpreadsheet object.
     * @param wristMotor The Talon to control the wrist.
     */
    Wrist(TaskMgr *scheduler, LogSpreadsheet *logger, TalonSRX *wristMotor);
    virtual ~Wrist();

    /**
     * Set the wrist position using Motion Magic.
     * @param position The position goal.
     */
    void SetPosition(double position);

    /**
     * Set the wrist position step.
     * @param position The position goal.
     */
    void SetPositionStep(double position);

    /**
     * Set the elevator power.
     * @param power The power being sent to the motor from -1.0 to 1.0.
     */
    void SetPower(double power);

    /**
     * Get the current position.
     * @return The current position in sensor units.
     */
    float GetPosition() const;

    /**
     * Zero the position.
     */
    void ZeroPosition();

    /**
     * Continously check wrist stuff.
     * @param mode The current robot mode.
     */
    void TaskPeriodic(RobotMode mode);

    TalonSRX *m_wristMotor; /**< The wrist Talon. */

private:
    /**
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
};
}
