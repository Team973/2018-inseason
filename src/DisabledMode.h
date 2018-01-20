#pragma once

#include "WPILib.h"
#include <iostream>
#include "src/info/RobotInfo.h"
#include "lib/helpers/JoystickHelper.h"
#include "src/Robot.h"
#include "src/AutonomousMode.h"
#include "lib/util/WrapDash.h"

using namespace frc;

namespace frc973 {
class Disabled {
public:
    typedef enum routine { none, forward } SelectedAutoRoutine;

    Disabled(ObservableJoystick *driver, ObservableJoystick *codriver,
             ObservableJoystick *tuning);
    virtual ~Disabled();

    void DisabledInit();
    void DisabledPeriodic();
    void DisabledStop();

    void HandleDisabledButton(uint32_t port, uint32_t button, bool pressedP);

    const char *GetRoutineName();
    SelectedAutoRoutine GetRoutine();
    int GetStartPosition();

private:
    SelectedAutoRoutine m_routine;

    ObservableJoystick *m_driverJoystick;
    ObservableJoystick *m_operatorJoystick;
    ObservableJoystick *m_tuningJoystick;

    int m_startPos;
};
};
