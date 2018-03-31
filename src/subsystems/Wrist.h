#pragma once

#include "WPILib.h"
#include "ctre/Phoenix.h"
#include "lib/managers/CoopTask.h"
#include "lib/logging/LogSpreadsheet.h"
#include "src/info/RobotInfo.h"
#include "lib/helpers/JoystickHelper.h"
#include "lib/util/Util.h"
#include "DigitalGlitchFilter.h"

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

    Wrist(TaskMgr *scheduler, LogSpreadsheet *logger,
          DigitalInput *rightCubeSensor, DigitalInput *leftCubeSensor,
          TalonSRX *wristMotor, TalonSRX *leftRoller, TalonSRX *rightRoller,
          Solenoid *cubeClamp);
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

    /*
     * When called, opens the claw arms
     */
    void OpenClaw();

    /*
     * When called, closes claw arms
     */
    void CloseClaw();

    void IntakeCube(double power);
    void EjectCube(double power);
    void StopIntake();

    bool IsCubeIn() const;

    void TaskPeriodic(RobotMode mode);

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
    WristState m_wristState;

    DigitalInput *m_rightCubeSensor;
    DigitalInput *m_leftCubeSensor;
    Solenoid *m_cubeClamp;

    TalonSRX *m_leftRoller;
    TalonSRX *m_rightRoller;

public:
    TalonSRX *m_wristMotor;

private:
    double m_position;
    double m_prevWristSetpoint;
    double m_wristPositionDelta;
    DigitalGlitchFilter *m_bannerFilter;
    uint32_t m_zeroingTime;
};
}
