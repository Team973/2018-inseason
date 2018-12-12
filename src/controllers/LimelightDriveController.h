/*
 *  LimelightDriveController.h
 *  Created: 4 December 2018
 */

#pragma once

#include "lib/bases/DriveBase.h"
#include "stdio.h"
#include "lib/util/Util.h"
#include "lib/sensors/Limelight.h"

namespace frc973 {

class PID;

class LimelightDriveController : public DriveController {
public:
    LimelightDriveController(Limelight *limelight);
    virtual ~LimelightDriveController();

    void Start(DriveControlSignalReceiver *out) override;

    void CalcDriveOutput(DriveStateProvider *state,
                         DriveControlSignalReceiver *out) override;

    bool OnTarget() override {
        return m_onTarget;
    };

    static constexpr double VISION_MIN_POWER = 0.01;

private:
    bool m_onTarget;
    double m_leftSetpoint;
    double m_rightSetpoint;

    Limelight *m_limelight;
    PID *m_pid;
};
}
