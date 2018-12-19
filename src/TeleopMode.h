/*
 * TeleopMode.h
 *
 *  Created on: January 7, 2018
 *      Authors: Kyle, Chris
 *
 *  Control map available at: https://goo.gl/MrViHA
 */
#pragma once

#include "WPILib.h"
#include <iostream>
#include "src/info/RobotInfo.h"
#include "lib/helpers/DualActionJoystickHelper.h"
#include "lib/helpers/XboxJoystickHelper.h"
#include "lib/helpers/PoofsJoystickHelper.h"
#include "src/subsystems/Drive.h"
#include "src/subsystems/IntakeAssembly.h"
#include "src/subsystems/Hanger.h"
#include "lib/helpers/GreyLight.h"
#include "lib/pixelprocessors/Flash.h"
#include "lib/pixelprocessors/SolidColor.h"
#include "lib/util/WrapDash.h"

using namespace frc;

namespace frc973 {

/**
 * Controls the teleop mode.
 */
class Teleop {
public:
    static constexpr Color END_GAME_RED = {
        255, 0, 0}; /**< Display red during end game. */
    static constexpr Color NO_COLOR = {0, 0, 0}; /**< Turn off the LED strip. */

    /**
     * Constuct a teleop mode.
     * @param driver The driver's joystick.
     * @param codriver The co-driver's joystick.
     * @param drive The drive subsystem.
     * @param intakeAssembly The intakeAssembly subsystem.
     * @param hanger The hanger subsystem.
     * @param greylight The GreyLight system.
     */
    Teleop(ObservableDualActionJoystick *driver,
           ObservableXboxJoystick *codriver, Drive *drive,
           IntakeAssembly *intakeAssembly, Hanger *hanger,
           GreyLight *greylight);
    virtual ~Teleop();

    /**
     * Start of teleop.
     */
    void TeleopInit();

    /**
     * Loop of teleop.
     */
    void TeleopPeriodic();

    /**
     * Stop of teleop.
     */
    void TeleopStop();

    /**
     * Button handler for the teleop mode.
     * @param port The port the joystick is connected to.
     * @param button The button.
     * @param pressedP The button's new status.
     */
    void HandleDualActionJoystick(uint32_t port, uint32_t button,
                                  bool pressedP);
    void HandleXboxJoystick(uint32_t port, uint32_t button, bool pressedP);
    void HandlePoofsJoystick(uint32_t port, uint32_t button, bool pressedP);

private:
    ObservableDualActionJoystick *m_driverJoystick;
    ObservableXboxJoystick *m_operatorJoystick;

    Drive *m_drive;
    enum class DriveMode
    {
        Cheesy,
        VelocityArcadeDrive,
        Hanger,
        Limelight
    };
    DriveMode m_driveMode;

    IntakeAssembly *m_intakeAssembly;
    enum class CubeIntakeState
    {
        Idle,
        SwitchIntaking,
        ManualIntaking,
        StopRumble,
        SwitchIntakeDelay
    };
    CubeIntakeState m_cubeIntakeState;

    enum class WristControlMode
    {
        ClosedLoop,
        OpenLoop
    };
    WristControlMode m_wristControlMode;
    Debouncer *m_wristControlModeDebouncer;
    bool m_wristModeSwitchPrevState;

    double m_elevatorPosition;

    uint32_t m_intakeModeTimer;

    bool m_endGameSignalSent;
    bool m_enableForkDeploy;

    Hanger *m_hanger;
    GreyLight *m_greyLight;
    LightPattern::Flash *m_endGameSignal;
    LightPattern::SolidColor *m_wristEmergencySignal;
    LightPattern::SolidColor *m_clear;
};
};
