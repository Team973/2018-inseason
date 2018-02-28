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
using namespace cs;

namespace frc973 {
class Disabled {
public:
    Disabled(ObservableJoystick *driver, ObservableJoystick *codriver,
             UsbCamera intakeCamera, UsbCamera forkCamera, VideoSink greyCam);
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

    UsbCamera m_intakeCamera;
    UsbCamera m_forkCamera;
    VideoSink m_greyCam;
    AutoRoutineBase::RobotStartPosition m_startPos;
};
};
