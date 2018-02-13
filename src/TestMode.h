#pragma once

#include "WPILib.h"
#include <iostream>
#include "src/info/RobotInfo.h"
#include "lib/helpers/JoystickHelper.h"
#include "lib/util/Util.h"
#include "src/subsystems/Drive.h"
#include "src/subsystems/Elevator.h"
#include "src/subsystems/Claw.h"

using namespace frc;

namespace frc973 {
class Test {
public:
    Test(ObservableJoystick *driver, ObservableJoystick *codriver, Drive *drive,
         Elevator *elevator, Claw *claw);
    virtual ~Test();

    void TestInit();
    void TestPeriodic();
    void TestStop();

    void HandleTestButton(uint32_t port, uint32_t button, bool pressedP);

private:
    enum ElevatorMode
    {
        percentOutput,
        motionMagic,
        zero
    };

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

    ObservableJoystick *m_driverJoystick;
    ObservableJoystick *m_operatorJoystick;
    Drive *m_drive;

    DriveMode m_driveMode;

    Elevator *m_elevator;
    Claw *m_claw;

    ElevatorMode m_elevatorMode;
};
}
