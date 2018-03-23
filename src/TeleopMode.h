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
#include "src/subsystems/Drive.h"
#include "src/subsystems/IntakeAssembly.h"
#include "src/subsystems/Hanger.h"
#include "lib/helpers/GreyLight.h"
#include "lib/pixelprocessors/Flash.h"
#include "lib/pixelprocessors/SolidColor.h"

using namespace frc;

namespace frc973 {
class Teleop {
public:
    static constexpr Color INTAKE_GREEN = {0, 255, 0};
    static constexpr Color END_GAME_RED = {255, 0, 0};
    static constexpr Color NO_COLOR = {0, 0, 0};

    Teleop(ObservableJoystick *driver, ObservableJoystick *codriver,
           IntakeAssembly *intakeAssembly, Hanger *hanger,
           GreyLight *greylight);
    virtual ~Teleop();

    void TeleopInit();
    void TeleopPeriodic();
    void TeleopStop();

    void HandleTeleopButton(uint32_t port, uint32_t button, bool pressedP);

private:
    ObservableJoystick *m_driverJoystick;
    ObservableJoystick *m_operatorJoystick;

    Drive *m_drive;
    enum class DriveMode
    {
        Cheesy,
        Hanger
    };
    DriveMode m_driveMode;

    IntakeAssembly *m_intakeAssembly;
    double m_elevatorPosition;

    enum class IntakeMode
    {
        manual,
        switchIntaking,
        switchTaking,
        switchGrabbing,
        switchStandby,
        vaultStart,
        vaultIntaking,
        vaultEjecting
    };
    IntakeMode m_intakeMode;
    uint32_t m_intakeModeTimer;

    bool m_endGameSignalSent;

    Hanger *m_hanger;
    GreyLight *m_greyLight;
    LightPattern::Flash *m_intakeSignal;
    LightPattern::Flash *m_endGameSignal;
    LightPattern::SolidColor *m_ptoSignal;
};
};
