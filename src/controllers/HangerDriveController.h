/*
 * HangerDriveController.h
 *
 *  Created on: Jan 25, 2018
 *      Author: Chris
 */

#pragma once

#include "lib/bases/DriveBase.h"
#include <stdio.h>

using namespace frc;

namespace frc973 {

/**
 * Hanger Drive controller.
 */
class HangerDriveController : public DriveController {
public:
    /**
     * Construct a Hanger Drive controller.
     */
    HangerDriveController();
    virtual ~HangerDriveController();

    /**
     * Calculate motor output given the most recent joystick commands. In this
     * case just return the most recent joystick commands.
     * @param state The state provider for handling incoming messages.
     * @param out The signal receiver for handling outgoing messages.
     */
    void CalcDriveOutput(DriveStateProvider *state,
                         DriveControlSignalReceiver *out);

    /**
     * Checks with the controller to see if we are on target.
     * @return false, this is an open-loop controller.
     */
    bool OnTarget() override {
        return false;
    }

    /**
     * Set the joystick values (which in this case will be output).
     * @param throttle Forward/backwards amount.
     */
    void SetJoysticks(double throttle);

    /**
     * Start the drive controller.
     * @param out The signal receiver for handling outgoing messages.
     */
    void Start(DriveControlSignalReceiver *out) override;

    /**
     * Stop the drive controller.
     * @param out The signal receiver for handling outgoing messages.
     */
    void Stop(DriveControlSignalReceiver *out) override;

private:
    double m_leftOutput;
    double m_rightOutput;
};
}
