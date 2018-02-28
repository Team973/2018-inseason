#pragma once

#include "WPILib.h"
#include <iostream>
#include "src/info/RobotInfo.h"
#include "lib/helpers/JoystickHelper.h"
#include "src/Robot.h"
#include "src/AutonomousMode.h"
#include "src/auto/AutoRoutineBase.h"
#include "lib/util/WrapDash.h"

using namespace frc;

namespace frc973 {
class Disabled {
public:
    Disabled(ObservableJoystick *driver, ObservableJoystick *codriver);
    virtual ~Disabled();

    void DisabledInit();
    void DisabledPeriodic();
    void DisabledStop();

    const char *RobotStartPosToString(
        AutoRoutineBase::RobotStartPosition position);

    void HandleDisabledButton(uint32_t port, uint32_t button, bool pressedP);

    AutoRoutineBase::RobotStartPosition GetStartPosition();

private:
    ObservableJoystick *m_driverJoystick;
    ObservableJoystick *m_operatorJoystick;

    AutoRoutineBase::RobotStartPosition m_startPos;
};
};
