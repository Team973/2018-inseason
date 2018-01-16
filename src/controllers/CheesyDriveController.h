/*
 * CheesyDriveController.h
 *
 *  Created on: Jan 15, 2018
 *      Author: Chris
 */

#pragma once

#include "lib/bases/DriveBase.h"
#include <stdio.h>

using namespace frc;
using namespace ctre;

namespace frc973 {

class CheesyDriveController : public DriveController {
public:
    CheesyDriveController();
    virtual ~CheesyDriveController();

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
    bool OnTarget() override { return false; }

    /*
    *  Set the joystick values
    */
    void SetJoysticks(double throttle, double turn, bool isQuickTurn,
                          bool isHighGear);

    void Start() override {
        printf("Turning on Cheesy Mode\n");
    }

    void Stop() override {
        printf("Turning off Cheesy Mode\n");
    }
private:
    double m_leftOutput;
    double m_rightOutput;

    double m_oldWheel;
    double m_quickStopAccumulator;
    double m_negInertiaAccumulator;

    /*
    * These factor determine how fast the turn traverses the "non linear" sine
    *  curve.
    */
    const double kHighWheelNonLinearity = 0.65;
    const double kLowWheelNonLinearity = 0.5;
    const double kHighNegInertiaScalar = 4.0;
    const double kLowNegInertiaThreshold = 0.65;
    const double kLowNegInertiaTurnScalar = 3.5;
    const double kLowNegInertiaCloseScalar = 4.0;
    const double kLowNegInertiaFarScalar = 5.0;
    const double kHighSensitivity = 0.95;
    const double kLowSensitivity = 1.3;
    const double kQuickStopDeadband = 0.2;
    const double kQuickStopWeight = 0.1;
    const double kQuickStopScalar = 5.0;

    double m_negInertia;
    double m_turnNonLinearity;

    double m_denominator;

    double m_leftPwm;
    double m_rightPwm;
    double m_overPower;
    double m_sensitivity;

    double m_angularPower;
    double m_linearPower;

    double m_negInertiaScalar;
    double m_negInertiaPower;

    double m_alpha;
};

}
