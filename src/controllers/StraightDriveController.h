/*
 * StraightDriveController.h
 *
 *  Created on: Nov 5, 2015
 *      Author: Andrew
 */

#pragma once

#include "lib/bases/DriveBase.h"
#include "lib/helpers/PID.h"
#include "lib/logging/LogSpreadsheet.h"
#include <stdio.h>

using namespace frc;

namespace frc973 {

/**
 * Straight Drive controller.
 */
class StraightDriveController : public DriveController {
public:
    /**
     * Construct a Straight Drive controller.
     */
    StraightDriveController();
    virtual ~StraightDriveController();

    /**
     * Sets target for robot to reach.
     * @param relativeTo Point relative to the new setpoint.
     * @param throttle Power to motors.
     * @param angle Angle to turn.
     * @param state The state provider for handling incoming messages.
     */
    void SetTarget(DriveBase::RelativeTo relativeTo, double throttle,
                   double angle, DriveStateProvider *state);

    /**
     * Calculate motor output given the most recent joystick commands.
     * In this case just return the most recent joystick commands.
     * @param state The state provider for handling incoming messages.
     * @param out The signal receiver for handling outgoing messages.
     */
    void CalcDriveOutput(DriveStateProvider *state,
                         DriveControlSignalReceiver *out) override;

    /**
     * Checks with the controller to see if we are on target.
     * @return false, doesn't need to check if we are on target.
     */
    bool OnTarget() override {
        return false;
    }

    /**
     * Start the drive controller.
     * @param out The signal receiver for handling outgoing messages.
     */
    void Start(DriveControlSignalReceiver *out) override {
        printf("Turning on Straight Mode\n");
    }

    /**
     * Stop the drive controller.
     * @param out The signal receiver for handling outgoing messages.
     */
    void Stop(DriveControlSignalReceiver *out) override {
        printf("Turning off Straight Mode\n");
    }

private:
    double m_throttle;
    double m_targetAngle;
    double m_prevAngle;

    PID *m_turnPID;
};
}
