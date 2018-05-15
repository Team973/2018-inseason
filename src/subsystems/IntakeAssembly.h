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

/**
 * Intake assembly subsystem.
 */
class IntakeAssembly : public CoopTask {
public:
    /**
     * Struct for intake presets.
     */
    struct IntakePreset {
        double elevatorPosition; /**< The elevator position. */
        double wristPosition;    /**< The wrist position. */

        /**
         * Construct an intake preset.
         * @param elevatorPosition_ The elevator position.
         * @param wristPosition_ The wrist position.
         */
        IntakePreset(double elevatorPosition_, double wristPosition_)
                : elevatorPosition(elevatorPosition_)
                , wristPosition(wristPosition_) {
        }

        /**
         * Checks two IntakePresets to see if they are equal.
         */
        inline bool operator==(const IntakePreset &rhs) const {
            return this->elevatorPosition == rhs.elevatorPosition &&
                   this->wristPosition == rhs.wristPosition;
        }
    };

    static constexpr Color NO_COLOR = {0, 0, 0}; /**< Black/off LED color. */
    static constexpr Color INTAKE_GREEN = {0, 255, 0}; /**< Intake color. */

    static constexpr double UPPER_WRIST_BOUND =
        90.0; /**< The upper wrist boundary. */
    static constexpr double OVER_BACK_FORK_LOWER_BOUND =
        -80.0; /**< The overhead fork lower boundary. */
    static constexpr double NOCOLLIDE_FORK_LOWER_BOUND =
        20.0; /**< The stow preset. */
    static constexpr double SWITCH_LOWER_BOUND =
        -30.0; /**< The switch lower boundary. */

    static constexpr double FORK_AVOIDANCE_MIN_HEIGHT =
        20.0; /**< The fork min height. */
    static constexpr double FORK_AVOIDANCE_MID_HEIGHT =
        31.0; /**< The fork middle height. */
    static constexpr double FORK_AVOIDANCE_MAX_HEIGHT =
        78.0; /**< The fork max height. */

    static const IntakePreset STOW_PRESET;     /**< The stow preset. */
    static const IntakePreset GROUND_PRESET;   /**< The ground preset. */
    static const IntakePreset VAULT_PRESET;    /**< The vault preset. */
    static const IntakePreset LOW_GOAL_PRESET; /**< The stow preset. */
    static const IntakePreset
        AUTO_LOW_GOAL_PRESET; /**< The auto low goal preset. */
    static const IntakePreset SCALE_LOW_PRESET; /**< The lower scale preset. */
    static const IntakePreset SCALE_MID_PRESET; /**< The middle scale preset. */
    static const IntakePreset
        SCALE_HIGH_PRESET;                      /**< The higher scale preset. */
    static const IntakePreset OVER_BACK_PRESET; /**< The overhead preset. */
    static const IntakePreset
        SECOND_STACK_PRESET;                    /**< The second stack preset. */
    static const IntakePreset HANGING_PRESET;   /**< The hang preset. */
    static const IntakePreset HALF_STOW_PRESET; /**< The half stow preset. */

    /**
     * Contruct an intake assembly.
     * @param scheduler TaskMgr object.
     * @param logger LogSpreadsheet object.
     * @param operatorJoystick The co-driver joystick.
     * @param elevator The elevator subsystem.
     * @param claw The claw subsystem.
     * @param wrist The wrist subsystem.
     * @param greylight The GreyLight instance to control LEDs.
     */
    IntakeAssembly(TaskMgr *scheduler, LogSpreadsheet *logger,
                   ObservableJoystick *operatorJoystick, Elevator *elevator,
                   Claw *claw, Wrist *wrist, GreyLight *greylight);
    virtual ~IntakeAssembly();

    /**
     * Go to an elevator+wrist position. This function does collision avoidance
     * so it might take a weird route to get to your end goal position.
     * @param intakePosition The position goal.
     */
    void GoToIntakePosition(IntakePreset intakePosition);

    /**
     * Set the manual power to the elevator.
     * @param input The power to input between -1.0 and 1.0.
     */
    void SetElevatorManualPower(double input);

    /**
     * Set the manual power to the wrist.
     * @param input The power to input between -1.0 and 1.0.
     */
    void SetWristManualPower(double input);

    /**
     * Set the position to manual input.
     */
    void SetPosManualInput();

    /**
     * Set the mode to hanging.
     * @param hanging The status of hanging or not.
     */
    void SetModeHanging(bool hanging);

    /**
     * Run the intake at a certain power.
     * @param input The power to input between -1.0 and 1.0.
     */
    void RunIntake(double input);

    void FastEjectCube(); /**< Eject the cube at the fast speed. */
    void EjectCube();     /**< Eject the cube at the regular speed.*/
    void HaltIntake();    /**< Pause the ejecting state at 0.0. */
    void SlowEjectCube(); /**< Eject the cube at the slow speed. */
    void HoldCube();      /**< Hold on to the cube by applying some pressure. */
    void StopIntake();    /**< Stop the intake. */

    void OpenClaw();      /**< Open the claw. */
    void SoftCloseClaw(); /**< Close the claw with soft pressure. */
    void HardCloseClaw(); /**< Close the claw with hard pressure. */

    /**
     * Get the current elevator position.
     * @return The current position.
     */
    double GetElevatorPosition();

    /**
     * Get the current wrist position.
     * @return The current position.
     */
    double GetWristPosition();

    void ZeroPosition(); /**< Zero the position of the elevator and wrist. */

    void EnableBrakeMode(); /**< Enable brake mode on the Talons. */
    void EnableCoastMode(); /**< Enable coast mode on the Talons. */

    /**
     * Get the wrist instance.
     * @return The wrist instance.
     */
    const Wrist *GetWrist();

    /**
     * Get the claw instance.
     * @return The claw instance.
     */
    const Claw *GetClaw();

    /**
     * Get the elevator instance.
     * @return The elevator instance.
     */
    const Elevator *GetElevator();

    /**
     * Get the wrist's lower boundary based on the elevator position.
     * @param elevatorPosition The position of the elevator.
     * @return The wrist's the lower boundary.
     */
    double GetWristLowerBound(double elevatorPosition);

    /**
     * Get the position error.
     * @return The position error.
     */
    double GetPositionError();
    double GetEndPositionError();

    void StartZeroPosition(); /**< Start zeroing. */
    void EndZeroPosition();   /**< End zeroing and set the zeros. */

    void Flash(); /**< Flash the lights for driver feedback. */

    void SetOpenLoopWrist(bool openLoop) {
        m_openLoopWrist = openLoop;
        if (!openLoop) {
            m_interimPositionGoal.wristPosition = GetWristPosition();
            m_controlMode = ControlMode::ManualPosition;
        }
    }

    /**
     * Update function synonymous to TeleopContinuous that gets called
     * continuously.
     * @param mode The current robot mode.
     */
    void TaskPeriodic(RobotMode mode);

private:
    /**
     * Used internally to go to a position. This method is unsafe because it
     * does not do collision avoidance.
     * @param posistion The preset to go to.
     */
    void SetPosition(IntakePreset position);

    enum class ControlMode
    {
        Idle,
        ManualPosition,
        ManualVoltage,
        VoltageWristPIDElevator,
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

    bool m_openLoopWrist;

    static constexpr double MAX_WRIST_SPEED = 180.0;
    static constexpr double MAX_ELEVATOR_SPEED = 50.0;
};
}
