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
    static constexpr double STOW = 0.0;
    static constexpr double OVER_THE_BACK = 135.0;

    Wrist(TaskMgr *scheduler, LogSpreadsheet *logger, DigitalInput *cubeSensor,
          TalonSRX *wristMotor, TalonSRX *leftRoller, TalonSRX *rightRoller,
          Solenoid *cubeClamp);
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
    TalonSRX *m_wristMotor;

    double m_position;
    uint32_t m_zeroingTime;
};
}
