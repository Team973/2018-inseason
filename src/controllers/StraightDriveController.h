/*
 * TrapDriveController.h
 */

#pragma once

#include "lib/bases/DriveBase.h"
#include "lib/helpers/PID.h"
#include "lib/logging/LogSpreadsheet.h"
#include <stdio.h>

using namespace frc;
using namespace ctre;

namespace frc973 {

class StraightDriveController : public DriveController {
public:
    StraightDriveController();
    virtual ~StraightDriveController();

    void SetTarget(DriveBase::RelativeTo relativeTo,
            double throttle, double angle,
            DriveStateProvider *state);

    void CalcDriveOutput(DriveStateProvider *state,
            DriveControlSignalReceiver *out) override;

    bool OnTarget() override { return false; }

    void Start() override {
        m_needSetControlMode = true;
    }

    void Stop() override {}

private:
    double m_throttle;
    double m_targetAngle;
    double m_prevAngle;
    bool m_needSetControlMode;
    phoenix::motorcontrol::ControlMode m_controlMode;

    PID *m_turnPID;
};

}
