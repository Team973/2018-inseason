/*
 * ArcadeDrive.h
 *
 *  Created on: Oct 30, 2015
 *      Author: Andrew
 */

#pragma once

#include "lib/bases/DriveBase.h"
#include <stdio.h>

using namespace frc;

namespace frc973 {

class OpenloopArcadeDriveController : public DriveController {
public:
    OpenloopArcadeDriveController();
    virtual ~OpenloopArcadeDriveController();

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

    void Start() override {
        m_needSetControlMode = true;
        printf("Turning on Arcade Mode\n");
    }

    void Stop() override {
        printf("Turning off arcade Mode\n");
    }

private:
    double m_leftOutput;
    double m_rightOutput;
    bool m_needSetControlMode;
};
}
