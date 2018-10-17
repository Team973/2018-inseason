#pragma once

#include "WPILib.h"
#include <iostream>
#include "src/info/RobotInfo.h"
#include "lib/helpers/DualActionJoystickHelper.h"
#include "lib/helpers/XboxJoystickHelper.h"
#include "lib/helpers/PoofsJoystickHelper.h"
#include "lib/util/Util.h"
#include "src/subsystems/Drive.h"
#include "src/subsystems/IntakeAssembly.h"
#include "src/subsystems/Hanger.h"
#include "lib/helpers/GreyLight.h"
#include "lib/pixelprocessors/Flash.h"

using namespace frc;

namespace frc973 {

/**
 * Controls the test mode.
 */
class Test {
public:
    /**
     * Constuct a test mode.
     * @param driver The driver's joystick.
     * @param codriver The co-driver's joystick.
     * @param drive The drive subsystem.
     * @param intakeAssembly The intakeAssembly subsystem.
     * @param hanger The hanger subsystem.
     * @param greylight The GreyLight system.
     */
    Test(ObservablePoofsJoystick *driver, ObservableXboxJoystick *codriver,
         Drive *drive, IntakeAssembly *intakeAssembly, Hanger *hanger,
         GreyLight *greylight);
    virtual ~Test();

    /**
     * Start of test.
     */
    void TestInit();

    /**
     * Loop of test.
     */
    void TestPeriodic();

    /**
     * Stop of test.
     */
    void TestStop();

    /**
     * Button handler for the test mode.
     * @param port The port the joystick is connected to.
     * @param button The button.
     * @param pressedP The button's new status.
     */
    void HandlePoofsJoystick(uint32_t port, uint32_t button, bool pressedP);
    void HandleXboxJoystick(uint32_t port, uint32_t button, bool pressedP);
    void HandleDualActionJoystick(uint32_t port, uint32_t button,
                                  bool pressedP);

private:
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

    enum class IntakeMode
    {
        manualPosition,
        manualVoltage,
        motionMagic
    };

    ObservablePoofsJoystick *m_driverJoystick;
    ObservableXboxJoystick *m_operatorJoystick;

    Drive *m_drive;
    DriveMode m_driveMode;
    IntakeMode m_intakeMode;
    IntakeAssembly *m_intakeAssembly;
    Hanger *m_hanger;

    GreyLight *m_greylight;
    LightPattern::Flash *m_flashSignal;
};
}
