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
#include "lib/helpers/GreyLight.h"
#include "lib/pixelprocessors/Flash.h"
#include "lib/filters/Debouncer.h"

using namespace frc;

namespace frc973 {
class TaskMgr;
class LogSpreadsheet;

class IntakeAssembly : public CoopTask {
public:
    static constexpr Color NO_COLOR = {0, 0, 0};
    static constexpr Color INTAKE_GREEN = {0, 255, 0};

    enum class IntakePosition
    {
        stow,
        ground,
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
        switchIntaking,
        switchStandby,
        vaultStart,
        vaultStop
    };

    IntakeAssembly(TaskMgr *scheduler, LogSpreadsheet *logger,
                   ObservableJoystick *operatorJoystick, Elevator *elevator,
                   Wrist *wrist, GreyLight *greylight);
    virtual ~IntakeAssembly();

    void GoToIntakePosition(IntakePosition intakePosition);

    void SetElevatorManualPower(double input);
    void SetWristManualPower(double input);

    void SetPosManualInput(double elevatorInc, double wristInc);

    void IntakeCube(double input);
    void VaultIntake();
    void EjectCube();
    void StopIntake();

    void DropCube();
    void GrabCube();

    double GetElevatorPosition();
    double GetWristPosition();

    void ZeroPosition();

    void EnableBrakeMode();
    void EnableCoastMode();

    const Wrist *GetWrist();
    const Elevator *GetElevator();

    /**
     * Update function synonymous to TeleopContinuous that gets called
     *continuously
     **/
    void TaskPeriodic(RobotMode mode);

private:
    TaskMgr *m_scheduler;

    ObservableJoystick *m_operatorJoystick;
    Elevator *m_elevator;
    Wrist *m_wrist;
    GreyLight *m_greyLight;
    LightPattern::Flash *m_intakeSignal;

    ControlMode m_controlMode;

    double m_elevatorPositionSetpoint;
    double m_wristPositionSetpoint;

    double m_elevatorInc, m_wristInc;

    static constexpr double MAX_WRIST_SPEED = 180.0;
    static constexpr double MAX_ELEVATOR_SPEED = 50.0;
};
}
