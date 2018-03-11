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
#include "src/subsystems/Elevator.h"
#include "src/subsystems/Claw.h"
#include "src/subsystems/Intake.h"
#include "src/subsystems/Hanger.h"
#include "lib/helpers/GreyLight.h"
#include "lib/pixelprocessors/Flash.h"
#include "lib/pixelprocessors/SolidColor.h"

using namespace frc;

namespace frc973 {
class Teleop {
public:
    Teleop(ObservableJoystick *driver, ObservableJoystick *codriver, Claw *claw,
           Drive *drive, Elevator *elevator, Intake *intake, Hanger *hanger,
           GreyLight *greylight);
    virtual ~Teleop();

    void TeleopInit();
    void TeleopPeriodic();
    void TeleopStop();

    void HandleTeleopButton(uint32_t port, uint32_t button, bool pressedP);

private:
    ObservableJoystick *m_driverJoystick;
    ObservableJoystick *m_operatorJoystick;
    uint32_t m_teleopTimer;

    Claw *m_claw;

    Drive *m_drive;
    enum class DriveMode
    {
        Cheesy,
        Hanger
    };
    DriveMode m_driveMode;

    enum class ElevatorMode
    {
        percentOutput,
        motionMagic,
        zeroingDown
    };

    Elevator *m_elevator;
    Intake *m_intake;

    ElevatorMode m_elevatorMode;
    double m_elevatorPosition;

    enum class IntakeMode
    {
        manual,
        switchIntaking,
        switchTaking,
        switchGrabbing,
        switchStandby,
        switchRaising,
        vaultStart,
        vaultIntaking,
        vaultEjecting
    };
    IntakeMode m_intakeMode;
    uint32_t m_intakeModeTimer;

    Hanger *m_hanger;
    GreyLight *m_greyLight;
    LightPattern::Flash *m_intakeSignal;
    LightPattern::Flash *m_endGameSignal;
    LightPattern::SolidColor *m_ptoSignal;
};
};
