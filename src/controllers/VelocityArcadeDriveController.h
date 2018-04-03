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

class VelocityArcadeDriveController : public DriveController {
public:
    VelocityArcadeDriveController();
    virtual ~VelocityArcadeDriveController();

    /*
     * Calculate motor output given the most recent joystick commands.
     * In this case just return the most recent joystick commands.
     */
    void CalcDriveOutput(DriveStateProvider *state,
                         DriveControlSignalReceiver *out);

    /*
     * This controller is open-loop so OnTarget doesn't make sense here...
     * just return false I guess...
     */
    bool OnTarget() override {
        return false;
    }

    /*
     * Set the joystick values (which in this case will be output)
     */
    void SetJoysticks(double throttle, double turn);

    void Start(DriveControlSignalReceiver *out) override {
        printf("Turning on Velocity Arcade Mode\n");
    }

    void Stop(DriveControlSignalReceiver *out) override {
        printf("Turning off Velocity Arcade Mode\n");
    }

private:
    double m_leftOutput;
    double m_rightOutput;
};
}
