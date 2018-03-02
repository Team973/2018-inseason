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
class HangerDriveController : public DriveController {
public:
    HangerDriveController();
    virtual ~HangerDriveController();

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
    void SetJoysticks(double throttle);

    void Start(DriveControlSignalReceiver *out) override;

    void Stop(DriveControlSignalReceiver *out) override;

private:
    double m_leftOutput;
    double m_rightOutput;
};
}
