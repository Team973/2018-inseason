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
    struct IntakePreset {
        double ElevatorPosition;
        double WristPosition;

        IntakePreset(double elevatorPosition_, double wristPosition_)
                : ElevatorPosition(elevatorPosition_)
                , WristPosition(wristPosition_) {
        }
    };

    static constexpr Color NO_COLOR = {0, 0, 0};
    static constexpr Color INTAKE_GREEN = {0, 255, 0};
    static constexpr double UPPER_WRIST_BOUND = 90.0;
    static constexpr double OVER_BACK_LOWER_BOUND = -80.0;
    static constexpr double FORK_LOWER_BOUND = 20.0;
    static constexpr double SWITCH_LOWER_BOUND = -30.0;

    const IntakePreset STOW_PRESET =
        IntakePreset(Elevator::GROUND, Wrist::STOW);
    const IntakePreset GROUND_PRESET =
        IntakePreset(Elevator::GROUND, Wrist::EXTENDED);
    const IntakePreset VAULT_PRESET =
        IntakePreset(Elevator::VAULT, Wrist::EXTENDED);
    const IntakePreset LOW_GOAL_PRESET =
        IntakePreset(Elevator::LOW_GOAL, Wrist::EXTENDED);
    const IntakePreset SCALE_LOW_PRESET =
        IntakePreset(Elevator::SCALE_LOW, Wrist::SCALE);
    const IntakePreset SCALE_MID_PRESET =
        IntakePreset(Elevator::SCALE_MID, Wrist::SCALE);
    const IntakePreset SCALE_HIGH_PRESET =
        IntakePreset(Elevator::SCALE_HIGH, Wrist::SCALE);
    const IntakePreset OVER_BACK_PRESET =
        IntakePreset(Elevator::SCALE_HIGH, Wrist::OVER_THE_BACK);

    IntakeAssembly(TaskMgr *scheduler, LogSpreadsheet *logger,
                   ObservableJoystick *operatorJoystick, Elevator *elevator,
                   Wrist *wrist, GreyLight *greylight);
    virtual ~IntakeAssembly();

    void GoToIntakePosition(IntakePosition intakePosition);

    void SetElevatorManualPower(double input);
    void SetWristManualPower(double input);

    void SetPosManualInput();

    void IntakeCube(double input);
    void VaultIntake();
    void EjectCube();
    void StopIntake();

    void DropCube();
    void GrabCube();

    double GetElevatorPosition();
    double GetWristPosition();

    void EnableBrakeMode();
    void EnableCoastMode();

    double GetWristLowerBound(double elevatorPosition);

    double GetPositionError();

    /**
     * Update function synonymous to TeleopContinuous that gets called
     *continuously
     **/
    void TaskPeriodic(RobotMode mode);

private:
    enum class ControlMode
    {
        Idle,
        ManualPosition,
        ManualVoltage,
        Position,
        switchIntaking,
        switchStandby,
        vaultStart,
        vaultStop,
        low,
        subFork,
        superFork,
        overBack
    };

    TaskMgr *m_scheduler;

    ObservableJoystick *m_operatorJoystick;
    Elevator *m_elevator;
    Wrist *m_wrist;
    GreyLight *m_greyLight;
    LightPattern::Flash *m_intakeSignal;

    ControlMode m_controlMode;
    IntakePreset m_presetGoal;

    double m_elevatorPositionSetpoint;
    double m_wristPositionSetpoint;

    double m_elevatorInc, m_wristInc;

    static constexpr double MAX_WRIST_SPEED = 180.0;
    static constexpr double MAX_ELEVATOR_SPEED = 50.0;
};
}
