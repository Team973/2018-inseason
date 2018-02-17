#pragma once

#include "WPILib.h"
#include <iostream>
#include "src/info/RobotInfo.h"
#include "lib/helpers/JoystickHelper.h"
#include "src/subsystems/Intake.h"

using namespace frc;

namespace frc973 {
class Teleop {
public:
    Teleop(ObservableJoystick *driver, ObservableJoystick *codriver,
           ObservableJoystick *tuning, Intake *intake);
    virtual ~Teleop();

    void TeleopInit();
    void TeleopPeriodic();
    void TeleopStop();

    void HandleTeleopButton(uint32_t port, uint32_t button, bool pressedP);

private:
    ObservableJoystick *m_driverJoystick;
    ObservableJoystick *m_operatorJoystick;
    ObservableJoystick *m_tuningJoystick;
    Intake *m_intake;
};
};
