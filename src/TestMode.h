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
class Test {
public:
    Test(PoofsJoystick *driver, XboxJoystick *codriver, Drive *drive,
         IntakeAssembly *intakeAssembly, Hanger *hanger, GreyLight *greylight);
    virtual ~Test();

    void TestInit();
    void TestPeriodic();
    void TestStop();

    void HandleTestButton(uint32_t port, uint32_t button, bool pressedP);

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

    PoofsJoystick *m_driverJoystick;
    XboxJoystick *m_operatorJoystick;

    Drive *m_drive;
    DriveMode m_driveMode;
    IntakeMode m_intakeMode;
    IntakeAssembly *m_intakeAssembly;
    Hanger *m_hanger;

    GreyLight *m_greylight;
    LightPattern::Flash *m_flashSignal;
};
}
