/*
 * HangerDriveController.cpp
 *
 *  Created on: Jan 25, 2018
 *      Author: Chris
 */

#include "src/controllers/HangerDriveController.h"
#include "lib/util/Util.h"
#include <stdio.h>
#include "lib/util/WrapDash.h"
#include "src/info/RobotInfo.h"

using namespace frc;

namespace frc973 {

HangerDriveController::HangerDriveController()
        : m_leftOutput(0.0), m_rightOutput(0.0) {
}

HangerDriveController::~HangerDriveController() {
}

void HangerDriveController::CalcDriveOutput(DriveStateProvider *state,
                                            DriveControlSignalReceiver *out) {
    out->SetDriveOutputVBus(m_leftOutput, m_rightOutput);
    DBStringPrintf(DBStringPos::DB_LINE4, "hanger l=%1.2lf r=%1.2lf",
                   m_leftOutput, m_rightOutput);
    // printf("hanger l=%1.2lf r=%1.2lf\n", m_leftOutput, m_rightOutput);
}

void HangerDriveController::SetJoysticks(double throttle) {
    throttle = fabs(Util::bound(throttle, -1.0, 1.0));

    m_leftOutput = throttle;
    m_rightOutput = throttle;

    // printf("left %lf  right %lf\n", m_leftOutput, m_rightOutput);
}

void HangerDriveController::Start(DriveControlSignalReceiver *out) {
    out->ConfigDriveCurrentLimit(20);
}

void HangerDriveController::Stop(DriveControlSignalReceiver *out) {
    out->DisableDriveCurrentLimit();
}
}
