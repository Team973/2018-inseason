/*
 * CheesyDriveController.cpp
 *
 *  Created on: Jan 15, 2018
 *      Authors: Oliver, Chris
 */

#include "src/controllers/CheesyDriveController.h"
#include "lib/util/Util.h"
#include <stdio.h>
#include "lib/util/WrapDash.h"
#include "src/info/RobotInfo.h"

using namespace frc;
using namespace ctre;

namespace frc973 {

CheesyDriveController::CheesyDriveController():
    m_leftOutput(0.0),
    m_rightOutput(0.0),
    m_needSetControlMode(true),
    m_oldWheel(0.0),
    m_quickStopAccumulator(0.0),
    m_negInertiaAccumulator(0.0) {
}

CheesyDriveController::~CheesyDriveController() {

}

void CheesyDriveController::CalcDriveOutput(DriveStateProvider *state,
        DriveControlSignalReceiver *out) {
    if(m_needSetControlMode == true){
        m_controlMode = phoenix::motorcontrol::ControlMode::Velocity;
        m_needSetControlMode = false;
    }
    out->SetDriveOutput(m_controlMode, m_leftOutput, m_rightOutput);
    DBStringPrintf(DBStringPos::DB_LINE4,
                "cheesy l=%1.2lf r=%1.2lf", m_leftOutput, m_rightOutput);
    //printf("cheesy l=%1.2lf r=%1.2lf\n", m_leftOutput, m_rightOutput);
}

void CheesyDriveController::SetJoysticks(double throttle, double turn, bool isQuickTurn, bool isHighGear) {
    m_negInertia = turn - m_oldWheel;
    m_oldWheel = turn;

    if (isHighGear) {
        m_turnNonLinearity = kHighWheelNonLinearity;
        m_denominator = sin(Constants::PI / 2.0 * m_turnNonLinearity);
        // Apply a sin function that's scaled to make it feel better.
        turn = sin(Constants::PI / 2.0 * m_turnNonLinearity * turn) / m_denominator;
        turn = sin(Constants::PI / 2.0 * m_turnNonLinearity * turn) / m_denominator;
    } else {
        m_turnNonLinearity = kLowWheelNonLinearity;
        m_denominator = sin(Constants::PI / 2.0 * m_turnNonLinearity);
        // Apply a sin function that's scaled to make it feel better.
        turn = sin(Constants::PI / 2.0 * m_turnNonLinearity * turn) / m_denominator;
        turn = sin(Constants::PI / 2.0 * m_turnNonLinearity * turn) / m_denominator;
        turn = sin(Constants::PI / 2.0 * m_turnNonLinearity * turn) / m_denominator;
    }

    // Negative inertia!
    if (isHighGear) {
        m_negInertiaScalar = kHighNegInertiaScalar;
        m_sensitivity = kHighSensitivity;
    } else {
        if (turn * m_negInertia > 0) {
            // If we are moving away from 0.0, aka, trying to get more turn.
            m_negInertiaScalar = kLowNegInertiaTurnScalar;
        } else {
            // Otherwise, we are attempting to go back to 0.0.
            if (fabs(turn) > kLowNegInertiaThreshold) {
                m_negInertiaScalar = kLowNegInertiaFarScalar;
            } else {
                m_negInertiaScalar = kLowNegInertiaCloseScalar;
            }
        }
        m_sensitivity = kLowSensitivity;
    }
    m_negInertiaPower = m_negInertia * m_negInertiaScalar;
    m_negInertiaAccumulator += m_negInertiaPower;

    turn = turn + m_negInertiaAccumulator;
    if (m_negInertiaAccumulator > 1) {
        m_negInertiaAccumulator -= 1;
    } else if (m_negInertiaAccumulator < -1) {
        m_negInertiaAccumulator += 1;
    } else {
        m_negInertiaAccumulator = 0;
    }
    m_linearPower = throttle;

    // Quickturn!
    if (isQuickTurn) {
        if (fabs(m_linearPower) < kQuickStopDeadband) {
            m_alpha = kQuickStopWeight;
            m_quickStopAccumulator = (1 - m_alpha) * m_quickStopAccumulator
                + m_alpha * limit(turn, 1.0) * kQuickStopScalar;
        }
        m_overPower = 1.0;
        m_angularPower = turn;
    } else {
        m_overPower = 0.0;
        m_angularPower = fabs(throttle) * turn * m_sensitivity - m_quickStopAccumulator;
        if (m_quickStopAccumulator > 1) {
            m_quickStopAccumulator -= 1;
        } else if (m_quickStopAccumulator < -1) {
            m_quickStopAccumulator += 1;
        } else {
            m_quickStopAccumulator = 0.0;
        }
    }

    m_rightPwm = m_leftPwm = m_linearPower;
    m_leftPwm += m_angularPower;
    m_rightPwm -= m_angularPower;

    if (m_leftPwm > 1.0) {
        m_rightPwm -= m_overPower * (m_leftPwm - 1.0);
        m_leftPwm = 1.0;
    } else if (m_rightPwm > 1.0) {
        m_leftPwm -= m_overPower * (m_rightPwm - 1.0);
        m_rightPwm = 1.0;
    } else if (m_leftPwm < -1.0) {
        m_rightPwm += m_overPower * (-1.0 - m_leftPwm);
        m_leftPwm = -1.0;
    } else if (m_rightPwm < -1.0) {
        m_leftPwm += m_overPower * (-1.0 - m_rightPwm);
        m_rightPwm = -1.0;
    }

    m_leftOutput = m_leftPwm;
    m_rightOutput = m_rightPwm;
}

double CheesyDriveController::limit(double x, double maxMagnitude) {
    return fmin(maxMagnitude, fmax(-maxMagnitude, x));
}

}
