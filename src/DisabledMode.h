#pragma once

#include "WPILib.h"
#include <iostream>
#include "src/info/RobotInfo.h"
#include "lib/helpers/JoystickHelper.h"
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

/**
 * Controls the disabled mode.
 */
class Disabled {
public:
    /**
     * Constuct a disabled mode.
     * @param driver The driver's joystick.
     * @param codriver The co-driver's joystick.
     * @param intakeAssembly The intakeAssembly subsystem.
     * @param intakeCamera The intake camera.
     * @param forkCamera The fork camera.
     * @param greyCam The camera server.
     * @param greylight The GreyLight system.
     */
    Disabled(ObservableJoystick *driver, ObservableJoystick *codriver,
             IntakeAssembly *intakeAssembly, UsbCamera intakeCamera,
             UsbCamera forkCamera, VideoSink greyCam, GreyLight *greylight);
    virtual ~Disabled();

    /**
     * Start of disabled.
     */
    void DisabledInit();

    /**
     * Loop of disabled.
     */
    void DisabledPeriodic();

    /**
     * Stop of disabled.
     */
    void DisabledStop();

    /**
     * Stringifies the robot start position.
     * @param position The robot's starting position.
     */
    const char *RobotStartPosToString(
        AutoRoutineBase::RobotStartPosition position);

    /**
     * Button handler for the disabled mode.
     * @param port The port the joystick is connected to.
     * @param button The button.
     * @param pressedP The button's new status.
     */
    void HandleDisabledButton(uint32_t port, uint32_t button, bool pressedP);

    /**
     * Gets the robot's start position.
     * @return The robot's start position.
     */
    AutoRoutineBase::RobotStartPosition GetStartPosition();

private:
    ObservableJoystick *m_driverJoystick;
    ObservableJoystick *m_operatorJoystick;

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
