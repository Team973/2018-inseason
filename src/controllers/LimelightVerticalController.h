/*
 *  LimelightVerticalController.h
 *  Created: 4 December 2018
 */

#pragma once

#include "stdio.h"
#include "lib/util/Util.h"
#include "lib/sensors/Limelight.h"
#include "ctre/Phoenix.h"

namespace frc973 {

class PID;

class LimelightVerticalController {
public:
    LimelightVerticalController(Limelight *limelight, TalonSRX *motor);
    virtual ~LimelightVerticalController();

    void CalcOutput();

    bool OnTarget() {
        return m_onTarget;
    };

    static constexpr double VELOCITY_MULTIPLIER = 50.0;

private:
    bool m_onTarget;
    double m_setpoint;

    Limelight *m_limelight;
    TalonSRX *m_motor;
};
}
