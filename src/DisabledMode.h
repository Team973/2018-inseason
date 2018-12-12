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
    Disabled(ObservableDualActionJoystick *driver,
             ObservableXboxJoystick *codriver, IntakeAssembly *intakeAssembly,
             UsbCamera intakeCamera, UsbCamera forkCamera, VideoSink greyCam,
             GreyLight *greylight);
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
    const char *AutoRoutineModeToString(AutoRoutineBase::AutoRoutineMode mode);

    /**
     * Button handler for the disabled mode.
     * @param port The port the joystick is connected to.
     * @param button The button.
     * @param pressedP The button's new status.
     */
    void HandleXboxJoystick(uint32_t port, uint32_t button, bool pressedP);
    void HandlePoofsJoystick(uint32_t port, uint32_t button, bool pressedP);
    void HandleDualActionJoystick(uint32_t port, uint32_t button,
                                  bool pressedP);

    /**
     * Gets the robot's start position.
     * @return The robot's start position.
     */
    AutoRoutineBase::RobotStartPosition GetStartPosition();
    AutoRoutineBase::AutoRoutineMode GetRoutineMode();

private:
    ObservableDualActionJoystick *m_driverJoystick;
    ObservableXboxJoystick *m_operatorJoystick;

    AutoRoutineBase::RobotStartPosition m_startPos;
    AutoRoutineBase::AutoRoutineMode m_routineMode;
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
