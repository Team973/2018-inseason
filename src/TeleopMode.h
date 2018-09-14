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
#include "lib/helpers/JoystickHelper.h"
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
class Teleop {
public:
    static constexpr Color END_GAME_RED = {255, 0, 0};
    static constexpr Color NO_COLOR = {0, 0, 0};

    static constexpr int LEFT_Y_AXIS_CHANNEL = 0;
    static constexpr int RIGHT_X_AXIS_CHANNEL = 3;

    static constexpr int RIGHT_BUMPER_CHANNEL = 4;
    static constexpr int RIGHT_TRIGGER_CHANNEL = 3;
    static constexpr int LEFT_BUMPER_CHANNEL = 2;
    static constexpr int LEFT_TRIGGER_CHANNEL = 1;

    Teleop(Joystick *driver, ObservableJoystick *codriver, Drive *drive,
           IntakeAssembly *intakeAssembly, Hanger *hanger,
           GreyLight *greylight);
    virtual ~Teleop();

    void TeleopInit();
    void TeleopPeriodic();
    void TeleopStop();

    void HandleTeleopButton(uint32_t port, uint32_t button, bool pressedP);
    void HandleXboxJoystick(uint32_t port, uint32_t button, bool pressedP);
    void HandlePoofsJoystick(uint32_t port, uint32_t button, bool pressedP);

private:
    Joystick *m_driverJoystick;
    ObservableJoystick *m_operatorJoystick;

    Drive *m_drive;
    enum class DriveMode
    {
        Cheesy,
        Hanger
    };
    DriveMode m_driveMode;

    IntakeAssembly *m_intakeAssembly;
    enum class CubeIntakeState
    {
        Idle,
        SwitchIntaking,
        ManualIntaking,
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
