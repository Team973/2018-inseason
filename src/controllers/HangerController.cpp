/*
 * HangerController.cpp
 *
 *  Created on: Jan 15, 2018
 *      Authors: Oliver, Chris
 */

#include "src/controllers/HangerController.h"
#include "lib/util/Util.h"
#include <stdio.h>
#include "lib/util/WrapDash.h"
#include "src/info/RobotInfo.h"

using namespace frc;
using namespace ctre;

namespace frc973 {

HangerController::HangerController() : m_leftOutput(0.0), m_rightOutput(0.0) {
}

HangerController::~HangerController() {
}

void HangerController::CalcDriveOutput(DriveStateProvider *state,
                                       DriveControlSignalReceiver *out) {
    out->SetDriveOutput(ControlMode::PercentOutput, m_leftOutput,
                        m_rightOutput);
    DBStringPrintf(DBStringPos::DB_LINE4, "hanger l=%1.2lf r=%1.2lf",
                   m_leftOutput, m_rightOutput);
    // printf("hanger l=%1.2lf r=%1.2lf\n", m_leftOutput, m_rightOutput);
}

void HangerController::SetJoysticks(double throttle) {
    throttle = Util::bound(fabs(throttle), -1.0, 1.0) * THROTTLE_MAX;

    double TURN_RAMPUP = 0.25;
    m_leftOutput =
        throttle - 0.5 * DRIVE_WIDTH * (TURN_RAMPUP * fabs(throttle));
    m_rightOutput =
        throttle + 0.5 * DRIVE_WIDTH * (TURN_RAMPUP * fabs(throttle));

    double maxSpeed = Util::max(m_leftOutput, m_rightOutput);
    if (maxSpeed > THROTTLE_MAX) {
        m_leftOutput = m_leftOutput * (THROTTLE_MAX / maxSpeed);
        m_rightOutput = m_rightOutput * (THROTTLE_MAX / maxSpeed);
    }

    // printf("left %lf  right %lf\n", m_leftOutput, m_rightOutput);
}
}
