#pragma once

#include "WPILib.h"
#include <iostream>
#include "lib/logging/LogSpreadsheet.h"

using namespace frc;

namespace frc973 {
class JoystickHelperBase {
public:
    static constexpr double DEADBAND_INPUT_THRESHOLD = 0.05;
    static constexpr double VIRTUAL_JOYSTICK_THRESHOLD = 0.5;

    JoystickHelperBase();

    virtual ~JoystickHelperBase();

    /**
     * This function is provided by the subclass to handle a joystick
     * button event notification.
     *
     * @param port Specifies the joystick port.
     * @param button Specifies the joystick button
     * @param newState If true, specifies the button has been pressed,
     *        if false, specifies the button has been released.
     */
    virtual void ObserveJoystickStateChange(uint32_t port, uint32_t button,
                                            bool newState) = 0;

    virtual float GetRawAxisWithDeadband(
        int axis, bool fSquared = false,
        double threshold = DEADBAND_INPUT_THRESHOLD);
};
};
