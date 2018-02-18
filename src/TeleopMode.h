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

using namespace frc;

namespace frc973 {
class Teleop {
public:
    enum ElevatorMode
    {
        percentOutput,
        motionMagic,
        zero
    };

    Teleop(ObservableJoystick *driver, ObservableJoystick *codriver, Claw *claw,
           Drive *drive, Elevator *elevator, Intake *intake);
    virtual ~Teleop();

    void TeleopInit();
    void TeleopPeriodic();
    void TeleopStop();

    void HandleTeleopButton(uint32_t port, uint32_t button, bool pressedP);

private:
    ObservableJoystick *m_driverJoystick;
    ObservableJoystick *m_operatorJoystick;

    Claw *m_claw;

    Drive *m_drive;
    enum DriveMode
    {
        Cheesy,
        Hanger
    };
    DriveMode m_driveMode;

    Elevator *m_elevator;
    Intake *m_intake;

    ElevatorMode m_elevatorMode;
    double m_elevatorPosition;

    enum class IntakeMode
    {
        Manual,
        Intaking,
        Grabbing,
        Raising
    };
    IntakeMode m_intakeMode;
    uint32_t m_intakeModeTimer;
};
};
