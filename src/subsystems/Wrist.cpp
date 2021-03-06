#include "src/subsystems/Wrist.h"
#include "WPILib.h"
#include "ctre/Phoenix.h"
#include "lib/util/WrapDash.h"

using namespace frc;
using namespace ctre::phoenix::motorcontrol;

namespace frc973 {
Wrist::Wrist(TaskMgr *scheduler, LogSpreadsheet *logger, TalonSRX *wristMotor,
             GreyLight *greylight)
        : m_wristMotor(wristMotor)
        , m_scheduler(scheduler)
        , m_greylight(greylight)
        , m_wristEmergencySignal(
              new LightPattern::Flash(WRIST_EMERGENCY_RED, {0, 0, 0}, 50, 30))
        , m_position(0.0)
        , m_prevWristSetpoint(0.0)
        , m_wristPositionDelta(0.0)
        , m_zeroingTime(0)
        , m_prevLimSwitchState(false) {
    this->m_scheduler->RegisterTask("Wrist", this, TASK_PERIODIC);

    m_wristMotor->ConfigSelectedFeedbackSensor(
        FeedbackDevice::CTRE_MagEncoder_Absolute, 0,
        10);  // 0 = Not cascaded PID Loop; 10 = in constructor, not in a loop
    m_wristMotor->SetSensorPhase(true);
    m_wristMotor->SetNeutralMode(NeutralMode::Coast);
    m_wristMotor->SetInverted(true);

    m_wristMotor->Config_kP(0, 3.5, 10);
    m_wristMotor->Config_kI(0, 0.0, 10);
    m_wristMotor->Config_kD(0, 0.0, 10);
    m_wristMotor->Config_kF(0, 0.0, 10);
    m_wristMotor->ConfigMotionCruiseVelocity(3750.0, 10);
    m_wristMotor->ConfigMotionAcceleration(3700.0, 10);
    m_wristMotor->SelectProfileSlot(0, 0);

    m_wristMotor->EnableCurrentLimit(true);
    m_wristMotor->ConfigPeakCurrentDuration(0, 10);
    m_wristMotor->ConfigPeakCurrentLimit(0, 10);
    m_wristMotor->ConfigContinuousCurrentLimit(10, 10);
    m_wristMotor->EnableVoltageCompensation(true);
    m_wristMotor->ConfigPeakOutputForward(0.5, 10);
    m_wristMotor->ConfigPeakOutputReverse(-0.5, 10);

    /*if (this->GetPosition() > 180.0) {
        m_wristMotor->SetSelectedSensorPosition(
            (int)((this->GetPosition() - 360) / WRIST_DEGREES_PER_CLICK), 0,
    10);
    }
    else if (this->GetPosition() < -180.0){
      m_wristMotor->SetSelectedSensorPosition(
          (int)((this->GetPosition() + 360) / WRIST_DEGREES_PER_CLICK), 0, 10);
    }*/

    /*
    m_wristMotor->ConfigForwardSoftLimitThreshold(
        DegreesToNativeUnits(WRIST_FORWARD_SOFT_LIMIT), 10);
    m_wristMotor->ConfigForwardSoftLimitEnable(true, 10);

    m_wristMotor->ConfigReverseSoftLimitThreshold(
        DegreesToNativeUnits(WRIST_REVERSE_SOFT_LIMIT), 10);
    m_wristMotor->ConfigReverseSoftLimitEnable(true, 10);
    */

    m_wristMotor->SetSelectedSensorPosition(DegreesToNativeUnits(-35.0), 0, 0);

    m_wristMotor->ConfigForwardLimitSwitchSource(
        LimitSwitchSource::LimitSwitchSource_FeedbackConnector,
        LimitSwitchNormal::LimitSwitchNormal_NormallyOpen, 10);
    m_wristMotor->ConfigReverseLimitSwitchSource(
        LimitSwitchSource::LimitSwitchSource_FeedbackConnector,
        LimitSwitchNormal::LimitSwitchNormal_NormallyOpen, 10);
    m_wristMotor->OverrideLimitSwitchesEnable(true);

    m_wristMotor->Set(ControlMode::PercentOutput, 0.0);

    m_limitSwitchStateCell = new LogCell("Limit switch state", 32, true);
    m_wristPositionCell = new LogCell("Wrist Position", 32, true);
    m_wristPulseWidthPosCell =
        new LogCell("Wrist Pulse Width Position", 32, true);

    logger->RegisterCell(m_limitSwitchStateCell);
    logger->RegisterCell(m_wristPositionCell);
    logger->RegisterCell(m_wristPulseWidthPosCell);
}

Wrist::~Wrist() {
    m_scheduler->UnregisterTask(this);
}

void Wrist::SetPower(double power) {
    m_wristMotor->Set(ControlMode::PercentOutput, power);
}

void Wrist::SetPosition(double position) {
    int position_clicks = DegreesToNativeUnits(
        Util::bound(position, WRIST_REVERSE_SOFT_LIMIT, 1000000));
    m_wristMotor->Set(ControlMode::MotionMagic, position_clicks);
}

void Wrist::SetPositionStep(double position) {
    int position_clicks = DegreesToNativeUnits(
        Util::bound(position, WRIST_REVERSE_SOFT_LIMIT, 1000000));
    m_wristMotor->Set(ControlMode::Position, position_clicks);
}

float Wrist::GetPosition() const {
    return NativeUnitsToDegrees(m_wristMotor->GetSelectedSensorPosition(0));
}

void Wrist::ZeroPosition() {
    m_wristMotor->SetSelectedSensorPosition(DegreesToNativeUnits(EXTENDED - 10),
                                            0, 0);
}

void Wrist::TaskPeriodic(RobotMode mode) {
    SmartDashboard::PutNumber("wrist/outputs/current",
                              m_wristMotor->GetOutputCurrent());
    DBStringPrintf(
        DBStringPos::DB_LINE7, "e %d pwp %d r %d f %d",
        m_wristMotor->GetClosedLoopError(0),
        m_wristMotor->GetSensorCollection().GetPulseWidthPosition(),
        m_wristMotor->GetSensorCollection().IsFwdLimitSwitchClosed(),
        m_wristMotor->GetSensorCollection().IsRevLimitSwitchClosed());

    if (fabs(GetPosition() - m_prevWristSetpoint) > 50.0) {
        m_wristEmergencySignal->Reset();
        m_greylight->SetPixelStateProcessor(m_wristEmergencySignal);
    }
    m_prevWristSetpoint = GetPosition();

    bool currLimSwitchState =
        m_wristMotor->GetSensorCollection().IsFwdLimitSwitchClosed();
    m_limitSwitchStateCell->LogInt(currLimSwitchState);
    m_wristPositionCell->LogDouble(GetPosition());

    if (m_prevLimSwitchState != currLimSwitchState) {
        ZeroPosition();
    }

    m_prevLimSwitchState = currLimSwitchState;
}

double Wrist::DegreesToNativeUnits(double degrees) const {
    // return 1500 - (degrees / WRIST_DEGREES_PER_CLICK);
    return degrees / WRIST_DEGREES_PER_CLICK + 1500;
}

double Wrist::NativeUnitsToDegrees(double nativeUnits) const {
    // return (1500 - nativeUnits) * WRIST_DEGREES_PER_CLICK;
    return (nativeUnits - 1500) * WRIST_DEGREES_PER_CLICK;
}
}
