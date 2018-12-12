#include "src/controllers/LimelightVerticalController.h"
#include "lib/util/WrapDash.h"
#include "stdio.h"

namespace frc973 {
LimelightVerticalController::LimelightVerticalController(Limelight *limelight,
                                                         TalonSRX *motor)
        : m_onTarget(false)
        , m_setpoint(0.0)
        , m_limelight(limelight)
        , m_motor(motor) {
}

LimelightVerticalController::~LimelightVerticalController() {
}

void LimelightVerticalController::CalcOutput() {
    double offset = m_limelight->GetYOffset();

    if (!m_limelight->isTargetValid()) {
        m_setpoint = 0.0;
    }
    else {
        m_setpoint = offset * VELOCITY_MULTIPLIER;
    }
    DBStringPrintf(DBStringPos::DB_LINE7, "s: %3.1lf", m_setpoint);

    m_motor->Set(ControlMode::Velocity, m_setpoint);

    if (fabs(offset) < 5.0) {
        m_onTarget = true;
    }
    else {
        m_onTarget = false;
    }
}
}
