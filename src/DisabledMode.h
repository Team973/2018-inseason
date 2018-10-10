#pragma once

#include "WPILib.h"
#include <iostream>
#include "src/info/RobotInfo.h"
#include "lib/helpers/DualActionJoystickHelper.h"
#include "lib/helpers/XboxJoystickHelper.h"
#include "lib/helpers/PoofsJoystickHelper.h"
#include "src/Robot.h"
#include "src/AutonomousMode.h"
#include "lib/util/WrapDash.h"
#include "src/auto/AutoRoutineBase.h"
#include "lib/helpers/GreyLight.h"
#include "lib/pixelprocessors/SolidColor.h"
#include "lib/pixelprocessors/LengthModifier.h"
#include "lib/pixelprocessors/ReverseModifier.h"

using namespace frc;
using namespace cs;

namespace frc973 {
class Disabled {
public:
    Disabled(ObservablePoofsJoystick *driver, ObservableXboxJoystick *codriver,
             IntakeAssembly *intakeAssembly, UsbCamera intakeCamera,
             UsbCamera forkCamera, VideoSink greyCam, GreyLight *greylight);
    virtual ~Disabled();

    void DisabledInit();
    void DisabledPeriodic();
    void DisabledStop();

    const char *RobotStartPosToString(
        AutoRoutineBase::RobotStartPosition position);

    void HandleDisabledButton(uint32_t port, uint32_t button, bool pressedP);

    AutoRoutineBase::RobotStartPosition GetStartPosition();

private:
    ObservablePoofsJoystick *m_driverJoystick;
    ObservableXboxJoystick *m_operatorJoystick;

    AutoRoutineBase::RobotStartPosition m_startPos;
    UsbCamera m_intakeCamera;
    UsbCamera m_forkCamera;
    VideoSink m_greyCam;

    GreyLight *m_greylight;
    IntakeAssembly *m_intakeAssembly;
    LightPattern::SolidColor *m_disabledSignal;
    LightPattern::LengthModifier *m_rightSideSignal;
    LightPattern::ReverseModifier *m_leftSideSignal;
};
};
