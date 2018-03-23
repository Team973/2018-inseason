#pragma once

#include "WPILib.h"
#include "ctre/Phoenix.h"
#include "lib/managers/CoopTask.h"
#include "lib/logging/LogSpreadsheet.h"
#include "src/info/RobotInfo.h"
#include "lib/helpers/JoystickHelper.h"
#include "lib/util/Util.h"
#include "src/subsystems/Elevator.h"
#include "src/subsystems/Wrist.h"

using namespace frc;

namespace frc973 {
class TaskMgr;
class LogSpreadsheet;

class IntakeAssembly : public CoopTask {
public:
    enum class IntakePosition
    {
        stow,
        vault,
        lowGoal,
        scaleLow,
        scaleMid,
        scaleHigh,
        overBack
    };

    enum class ControlMode
    {
        Idle,
        ManualPosition,
        ManualVoltage,
        Position,
    };

    IntakeAssembly(TaskMgr *scheduler, LogSpreadsheet *logger,
                   Elevator *elevator, Wrist *wrist);
    virtual ~IntakeAssembly();

    void GoToIntakePosition(IntakePosition intakePosition);

    void SetElevatorManualPower(double input);
    void SetWristManualPower(double input);

    void SetPosManualInput(double elevatorInc, double wristInc);

    void IntakeCube();
    void EjectCube();
    void StopIntake();

    double GetElevatorPosition();
    double GetWristPosition();

    /**
     * Update function synonymous to TeleopContinuous that gets called
     *continuously
     **/
    void TaskPeriodic(RobotMode mode);

private:
    TaskMgr *m_scheduler;

    Elevator *m_elevator;
    Wrist *m_wrist;

    ControlMode m_controlMode;

    double m_elevatorPositionSetpoint;
    double m_wristPositionSetpoint;

    double m_elevatorInc, m_wristInc;

    static constexpr double MAX_WRIST_SPEED = 180.0;
    static constexpr double MAX_ELEVATOR_SPEED = 50.0;
};
}
