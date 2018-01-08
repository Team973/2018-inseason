/*
 * TrapDriveController.h
 */

#pragma once

#include "src/lib/bases/DriveBase.h"
#include "src/lib/helpers/PID.h"
#include "src/lib/logging/LogSpreadsheet.h"
#include <stdio.h>

using namespace frc;

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

    PID *m_turnPID;
};

}
