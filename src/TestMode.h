#pragma once

#include "WPILib.h"
#include <iostream>
#include "src/info/RobotInfo.h"
#include "lib/helpers/JoystickHelper.h"
#include "lib/util/Util.h"
#include "src/subsystems/Drive.h"
#include "src/subsystems/Elevator.h"

using namespace frc;

namespace frc973 {
class Test {
public:
    enum ElevatorMode
    {
        percentOutput,
        motionMagic,
        position
    };
    Test(ObservableJoystick *driver, ObservableJoystick *codriver,
         ObservableJoystick *tuning, Drive *drive, Elevator *elevator);
    virtual ~Test();

    void TestInit();
    void TestPeriodic();
    void TestStop();

    void HandleTestButton(uint32_t port, uint32_t button, bool pressedP);

private:
    ObservableJoystick *m_driverJoystick;
    ObservableJoystick *m_operatorJoystick;
    ObservableJoystick *m_tuningJoystick;
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
