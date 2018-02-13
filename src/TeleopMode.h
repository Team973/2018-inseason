#pragma once

#include "WPILib.h"
#include <iostream>
#include "src/info/RobotInfo.h"
#include "lib/helpers/JoystickHelper.h"
#include "src/subsystems/Drive.h"
#include "src/subsystems/Elevator.h"
#include "src/subsystems/Claw.h"

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
           Drive *drive, Elevator *elevator);
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
        AssistedArcade,
        Cheesy,
        Hanger,
        Openloop,
        PID,
        Spline,
        Straight,
        Trap,
        Velocity
    };
    DriveMode m_driveMode;

    Elevator *m_elevator;

    ElevatorMode m_elevatorMode;
    double m_elevatorPosition;
};
};
