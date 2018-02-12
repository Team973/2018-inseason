#pragma once

#include "WPILib.h"
#include <iostream>
#include "src/info/RobotInfo.h"
#include "lib/helpers/JoystickHelper.h"
#include "src/Robot.h"
#include "src/AutonomousMode.h"

using namespace frc;
using namespace cs;

namespace frc973 {
class Disabled {
public:
    typedef enum routine { none, forward } SelectedAutoRoutine;

    Disabled(ObservableJoystick *driver, ObservableJoystick *codriver,
             ObservableJoystick *tuning, UsbCamera forkCamera,
             UsbCamera intakeCamera, VideoSink cameraServer);
    virtual ~Disabled();

    void DisabledInit();
    void DisabledPeriodic();
    void DisabledStop();

    void HandleDisabledButton(uint32_t port, uint32_t button, bool pressedP);

    const char *GetRoutineName();
    SelectedAutoRoutine GetRoutine();

private:
    SelectedAutoRoutine m_routine;

    ObservableJoystick *m_driverJoystick;
    ObservableJoystick *m_operatorJoystick;
    ObservableJoystick *m_tuningJoystick;

    UsbCamera m_forkCamera;
    UsbCamera m_intakeCamera;
    VideoSink m_cameraServer;
};
};
