/*
 * StraightDriveController.cpp
 *
 *  Created on: Nov 5, 2015
 *      Author: Andrew
 */

#include "src/controllers/StraightDriveController.h"
#include "lib/helpers/PID.h"
#include <stdio.h>
#include "lib/util/WrapDash.h"

using namespace frc;
using namespace ctre;

namespace frc973 {

static constexpr double TURN_PID_KP = 0.02;
static constexpr double TURN_PID_KI = 0.0;
static constexpr double TURN_PID_KD = 0.0005;

StraightDriveController::StraightDriveController()
        : m_throttle(0.0), m_targetAngle(0.0) {
    m_turnPID = new PID(TURN_PID_KP, TURN_PID_KI, TURN_PID_KD);
}

StraightDriveController::~StraightDriveController() {
    delete m_turnPID;
}

void StraightDriveController::CalcDriveOutput(DriveStateProvider *state,
                                              DriveControlSignalReceiver *out) {
    m_prevAngle = state->GetAngle();
    double turn = Util::bound(m_turnPID->CalcOutput(m_prevAngle), -0.5, 0.5);
    double throttle = m_throttle;

    out->SetDriveOutputVBus(-throttle + turn, -throttle - turn);
}

/*
 * dist and angle are relative to current position
 */
void StraightDriveController::SetTarget(DriveBase::RelativeTo relativity,
                                        double throttle, double angle,
                                        DriveStateProvider *state) {
    m_turnPID->Reset();
    m_throttle = throttle;

    switch (relativity) {
        case DriveBase::RelativeTo::Absolute:
            m_targetAngle = angle;
            break;
        case DriveBase::RelativeTo::Now:
            m_targetAngle = state->GetAngle() + angle;
            break;
        case DriveBase::RelativeTo::SetPoint:
            m_targetAngle = m_targetAngle + angle;
            break;
    }

    m_turnPID->SetTarget(m_targetAngle);
}
}
