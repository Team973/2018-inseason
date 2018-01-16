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
using namespace ctre;

namespace frc973 {

class AssistedArcadeDriveController : public DriveController {
public:
    AssistedArcadeDriveController();
    virtual ~AssistedArcadeDriveController();

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
    bool OnTarget() override { return true; }

    /*
     * Set the joystick values (which in this case will be output)
     */
    void SetJoysticks(double throttle, double turn);

    void Start() override {
        printf("Turning on Assisted Arcade Mode\n");
    }

    void Stop() override {
        printf("Turning off Assisted Arcade Mode\n");
    }
private:
    double m_throttle;
    double m_turn;
};

}
