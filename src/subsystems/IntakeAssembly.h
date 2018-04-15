#pragma once

#include "WPILib.h"
#include "ctre/Phoenix.h"
#include "lib/managers/CoopTask.h"
#include "lib/logging/LogSpreadsheet.h"
#include "src/info/RobotInfo.h"
#include "lib/helpers/JoystickHelper.h"
#include "lib/util/Util.h"
#include "src/subsystems/Elevator.h"
#include "src/subsystems/Claw.h"
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
        double elevatorPosition;
        double wristPosition;

        IntakePreset(double elevatorPosition_, double wristPosition_)
                : elevatorPosition(elevatorPosition_)
                , wristPosition(wristPosition_) {
        }

        inline bool operator==(const IntakePreset &rhs) const {
            return this->elevatorPosition == rhs.elevatorPosition &&
                   this->wristPosition == rhs.wristPosition;
        }
    };

    static constexpr Color NO_COLOR = {0, 0, 0};
    static constexpr Color INTAKE_GREEN = {0, 255, 0};

    static constexpr double UPPER_WRIST_BOUND = 90.0;
    static constexpr double OVER_BACK_FORK_LOWER_BOUND = -80.0;
    static constexpr double NOCOLLIDE_FORK_LOWER_BOUND = 20.0;
    static constexpr double SWITCH_LOWER_BOUND = -30.0;

    static constexpr double FORK_AVOIDANCE_MIN_HEIGHT = 20.0;
    static constexpr double FORK_AVOIDANCE_MID_HEIGHT = 31.0;
    static constexpr double FORK_AVOIDANCE_MAX_HEIGHT = 78.0;

    static const IntakePreset STOW_PRESET;
    static const IntakePreset GROUND_PRESET;
    static const IntakePreset VAULT_PRESET;
    static const IntakePreset LOW_GOAL_PRESET;
    static const IntakePreset SCALE_LOW_PRESET;
    static const IntakePreset SCALE_MID_PRESET;
    static const IntakePreset SCALE_HIGH_PRESET;
    static const IntakePreset OVER_BACK_PRESET;
    static const IntakePreset SECOND_STACK_PRESET;
    static const IntakePreset HANGING_PRESET;
    static const IntakePreset HALF_STOW_PRESET;

    IntakeAssembly(TaskMgr *scheduler, LogSpreadsheet *logger,
                   ObservableJoystick *operatorJoystick, Elevator *elevator,
                   Claw *claw, Wrist *wrist, GreyLight *greylight);
    virtual ~IntakeAssembly();

    /**
     * Go to an elevator+wrist position.  This function does collision
     * avoidance so it might take a weird route to get to your
     * end goal position
     */
    void GoToIntakePosition(IntakePreset intakePosition);

    void SetElevatorManualPower(double input);
    void SetWristManualPower(double input);

    void SetPosManualInput();
    void SetModeHanging(bool hanging);

    void RunIntake(double input);

    void FastEjectCube();
    void EjectCube();
    void HaltIntake();
    void SlowEjectCube();
    void HoldCube();
    void StopIntake();

    void OpenClaw();
    void SoftCloseClaw();
    void HardCloseClaw();

    double GetElevatorPosition();
    double GetWristPosition();

    void ZeroPosition();

    void EnableBrakeMode();
    void EnableCoastMode();

    const Wrist *GetWrist();
    const Claw *GetClaw();
    const Elevator *GetElevator();

    double GetWristLowerBound(double elevatorPosition);

    double GetPositionError();
    double GetEndPositionError();

    void StartZeroPosition();
    void EndZeroPosition();

    void Flash();

    /**
     * Update function synonymous to TeleopContinuous that gets called
     *continuously
     **/
    void TaskPeriodic(RobotMode mode);

private:
    /**
     * Used internally to go to a position.  This method is unsafe
     * because it does not do collision avoidance
     */
    void SetPosition(IntakePreset position);

    enum class ControlMode
    {
        Idle,
        ManualPosition,
        ManualVoltage,
        Zeroing,
        LowPosition,
        SubForkPosition,
        SuperForkPosition,
        OverBackPosition,
        PreHanging,
        HangingAuto,
        HangingManual
    };

    TaskMgr *m_scheduler;

    ObservableJoystick *m_operatorJoystick;
    Elevator *m_elevator;
    Claw *m_claw;
    Wrist *m_wrist;
    GreyLight *m_greyLight;
    LightPattern::Flash *m_intakeSignal;

    ControlMode m_controlMode;

    IntakePreset m_endPositionGoal;
    IntakePreset m_interimPositionGoal;

    static constexpr double MAX_WRIST_SPEED = 180.0;
    static constexpr double MAX_ELEVATOR_SPEED = 50.0;
};
}
