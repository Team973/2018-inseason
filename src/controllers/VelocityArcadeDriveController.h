/*
 * VelocityArcadeDriveController.h
 *
 *  Created on: Feb 3, 2018
 *      Author: Kyle
 */

#pragma once

#include "lib/bases/DriveBase.h"
#include <stdio.h>

using namespace frc;

namespace frc973 {

/**
 * Velocity Arcade Drive controller.
 */
class VelocityArcadeDriveController : public DriveController {
public:
    /**
     * Construct a Velocity Arcade Drive controller.
     */
    VelocityArcadeDriveController();
    virtual ~VelocityArcadeDriveController();

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
     * @return false, this controller is open-loop.
     */
    bool OnTarget() override {
        return false;
    }

    /**
     * Set the joystick values (which in this case will be output).
     * @param throttle Forward/backwards amount.
     * @param turn Left/right amount.
     */
    void SetJoysticks(double throttle, double turn);

    /**
     * Start the drive controller.
     * @param out The signal receiver for handling outgoing messages.
     */
    void Start(DriveControlSignalReceiver *out) override {
        printf("Turning on Velocity Arcade Mode\n");
    }

    /**
     * Stop the drive controller.
     * @param out The signal receiver for handling outgoing messages.
     */
    void Stop(DriveControlSignalReceiver *out) override {
        printf("Turning off Velocity Arcade Mode\n");
    }

private:
    double m_leftOutput;
    double m_rightOutput;
};
}
