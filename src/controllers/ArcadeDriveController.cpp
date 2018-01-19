/*
 * ArcadeDrive.cpp
 *
 *  Created on: Oct 30, 2015
 *      Author: Andrew
 */

#include "src/controllers/ArcadeDriveController.h"
#include "lib/util/Util.h"
#include <stdio.h>
#include <math.h>
#include "lib/util/WrapDash.h"
#include "src/info/RobotInfo.h"

namespace frc973 {

ArcadeDriveController::ArcadeDriveController()
        : m_leftOutput(0.0), m_rightOutput(0.0), m_needSetControlMode(true) {
}

ArcadeDriveController::~ArcadeDriveController() {
}

void ArcadeDriveController::CalcDriveOutput(DriveStateProvider *state,
                                            DriveControlSignalReceiver *out) {
    if (m_needSetControlMode == true) {
        out->SetDriveControlMode(
            ctre::phoenix::motorcontrol::ControlMode::Velocity);
        m_needSetControlMode = false;
    }

    out->SetDriveOutput(m_leftOutput, m_rightOutput);
    DBStringPrintf(DBStringPos::DB_LINE4, "arcade l=%1.2lf r=%1.2lf",
                   m_leftOutput, m_rightOutput);
    // printf("arcade l=%1.2lf r=%1.2lf\n", m_leftOutput, m_rightOutput);
}

void ArcadeDriveController::SetJoysticks(double throttle, double turn) {
    throttle = Util::bound(throttle, -1.0, 1.0) * THROTTLE_MAX;
    turn = Util::bound(turn, -1.0, 1.0) * TURN_MAX;

    double TURN_RAMPUP = 0.25;
    m_leftOutput = throttle - 0.5 * DRIVE_WIDTH *
                                  (TURN_RAMPUP * fabs(throttle) * turn + turn);
    m_rightOutput = throttle + 0.5 * DRIVE_WIDTH *
                                   (TURN_RAMPUP * fabs(throttle) * turn + turn);

    double maxSpeed = Util::max(m_leftOutput, m_rightOutput);
    if (maxSpeed > THROTTLE_MAX) {
        m_leftOutput = m_leftOutput * (THROTTLE_MAX / maxSpeed);
        m_rightOutput = m_rightOutput * (THROTTLE_MAX / maxSpeed);
    }

    // printf("left %lf  right %lf\n", m_leftOutput, m_rightOutput);
}
}
