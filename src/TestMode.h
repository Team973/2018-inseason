#pragma once

#include "WPILib.h"
#include <iostream>
#include "src/info/RobotInfo.h"
#include "lib/helpers/JoystickHelper.h"
#include "lib/util/Util.h"
#include "src/subsystems/Elevator.h"
#include "src/subsystems/Claw.h"

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
         ObservableJoystick *tuning, Elevator *elevator, Claw *claw);
    virtual ~Test();

    void TestInit();
    void TestPeriodic();
    void TestStop();

    void HandleTestButton(uint32_t port, uint32_t button, bool pressedP);

private:
    ObservableJoystick *m_driverJoystick;
    ObservableJoystick *m_operatorJoystick;
    ObservableJoystick *m_tuningJoystick;

    Elevator *m_elevator;
    Claw *m_claw;

    ElevatorMode m_elevatorMode;
    double m_elevatorPosition;
};
};
