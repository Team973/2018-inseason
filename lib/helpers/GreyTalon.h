#include "WPILib.h"
#include "Phoenix.h"

namespace frc973 {
TalonSRX* FactoryReset(TalonSRX* motor) {
    motor->ConfigSelectedFeedbackSensor(
        FeedbackDevice::None, 0,
        10);  // 0 = Not cascaded PID Loop; 10 = in constructor, not in a loop
    motor->SetSensorPhase(false);
    motor->SetInverted(false);
    motor->SetNeutralMode(NeutralMode::Coast);

    motor->ConfigOpenloopRamp(0, 10);
    motor->ConfigClosedloopRamp(0, 10);

    motor->ConfigNominalOutputForward(0.0, 10);
    motor->ConfigNominalOutputReverse(0.0, 10);
    motor->ConfigPeakOutputForward(1.0, 10);
    motor->ConfigPeakOutputReverse(-1.0, 10);
    motor->ConfigNeutralDeadband(0.04, 10);

    // Gains
    motor->Config_kP(0, 0.0, 10);
    motor->Config_kI(0, 0.0, 10);
    motor->Config_kD(0, 0.0, 10);
    motor->Config_kF(0, 0.0, 10);
    motor->ConfigMotionCruiseVelocity(0.0, 10);
    motor->ConfigMotionAcceleration(0.0, 10);

    // Limiting
    motor->EnableCurrentLimit(false);
    motor->ConfigPeakCurrentDuration(0, 10);
    motor->ConfigPeakCurrentLimit(0, 10);
    motor->ConfigContinuousCurrentLimit(0, 10);
    motor->EnableVoltageCompensation(false);
    motor->ConfigVoltageCompSaturation(12, 10);

    motor->Set(ControlMode::PercentOutput, 0.0);

    return motor;
}
}
