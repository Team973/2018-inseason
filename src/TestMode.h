#pragma once

#include "WPILib.h"
#include <iostream>
#include "src/info/RobotInfo.h"
#include "lib/helpers/JoystickHelper.h"
#include "lib/util/Util.h"
#include "src/subsystems/Drive.h"
#include "src/subsystems/Elevator.h"
#include "src/subsystems/Claw.h"
#include "src/subsystems/Hanger.h"

using namespace frc;

namespace frc973 {
class Test {
public:
    Test(ObservableJoystick *driver, ObservableJoystick *codriver,
         ObservableJoystick *tuning, Drive *drive, Elevator *elevator,
         Claw *claw, Hanger *hanger);
    virtual ~Test();

    void TestInit();
    void TestPeriodic();
    void TestStop();

    void HandleTestButton(uint32_t port, uint32_t button, bool pressedP);

private:
    enum class ElevatorMode
    {
        percentOutput,
        motionMagic,
        zero
    };

    enum class DriveMode
    {
        AssistedArcade,
        Cheesy,
        Hanger,
        Openloop,
        PID,
        ConstantArcSpline,
        Spline,
        Straight,
        Trap,
        Velocity
    };

    ObservableJoystick *m_driverJoystick;
    ObservableJoystick *m_operatorJoystick;
    ObservableJoystick *m_tuningJoystick;

    Drive *m_drive;
    DriveMode m_driveMode;
    Elevator *m_elevator;
    Claw *m_claw;
    Hanger *m_hanger;

    ElevatorMode m_elevatorMode;
};
};
