#include "src/subsystems/Wrist.h"
#include "WPILib.h"
#include "ctre/Phoenix.h"
#include "lib/util/WrapDash.h"

using namespace frc;
using namespace ctre::phoenix::motorcontrol;

namespace frc973 {
Wrist::Wrist(TaskMgr *scheduler, LogSpreadsheet *logger,
             DigitalInput *rightCubeSensor, DigitalInput *leftCubeSensor,
             TalonSRX *wristMotor, TalonSRX *leftRoller, TalonSRX *rightRoller,
             Solenoid *cubeClamp)
        : m_scheduler(scheduler)
        , m_wristState(WristState::manualVoltage)
        , m_rightCubeSensor(rightCubeSensor)
        , m_leftCubeSensor(leftCubeSensor)
        , m_cubeClamp(cubeClamp)
        , m_leftRoller(leftRoller)
        , m_rightRoller(rightRoller)
        , m_wristMotor(wristMotor)
        , m_position(0.0)
        , m_prevWristSetpoint(0.0)
        , m_wristPositionDelta(0.0)
        , m_bannerFilter(new DigitalGlitchFilter())
        , m_zeroingTime(0) {
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
    m_wristMotor->ConfigMotionAcceleration(3200.0, 10);
    m_wristMotor->SelectProfileSlot(0, 0);

    m_wristMotor->EnableCurrentLimit(true);
    m_wristMotor->ConfigPeakCurrentDuration(0, 10);
    m_wristMotor->ConfigPeakCurrentLimit(0, 10);
    m_wristMotor->ConfigContinuousCurrentLimit(5, 10);
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

    m_wristMotor->SetSelectedSensorPosition(DegreesToNativeUnits(-30.0), 0, 0);

    m_wristMotor->ConfigForwardLimitSwitchSource(
        LimitSwitchSource::LimitSwitchSource_FeedbackConnector,
        LimitSwitchNormal::LimitSwitchNormal_NormallyOpen, 10);
    m_wristMotor->ConfigReverseLimitSwitchSource(
        LimitSwitchSource::LimitSwitchSource_FeedbackConnector,
        LimitSwitchNormal::LimitSwitchNormal_NormallyOpen, 10);
    m_wristMotor->OverrideLimitSwitchesEnable(true);

    m_wristMotor->Set(ControlMode::PercentOutput, 0.0);

    m_leftRoller->SetNeutralMode(NeutralMode::Brake);

    m_rightRoller->SetNeutralMode(NeutralMode::Brake);
    m_rightRoller->SetInverted(true);

    m_leftRoller->Set(ControlMode::PercentOutput, 0.0);
    m_rightRoller->Set(ControlMode::PercentOutput, 0.0);

    m_leftRoller->EnableCurrentLimit(true);
    m_leftRoller->ConfigPeakCurrentDuration(0, 10);
    m_leftRoller->ConfigPeakCurrentLimit(0, 10);
    m_leftRoller->ConfigContinuousCurrentLimit(50, 10);

    m_rightRoller->EnableCurrentLimit(true);
    m_rightRoller->ConfigPeakCurrentDuration(0, 10);
    m_rightRoller->ConfigPeakCurrentLimit(0, 10);
    m_rightRoller->ConfigContinuousCurrentLimit(50, 10);

    m_bannerFilter->Add(m_leftCubeSensor);
    m_bannerFilter->Add(m_rightCubeSensor);
    m_bannerFilter->SetPeriodNanoSeconds(80000);
}

Wrist::~Wrist() {
    m_scheduler->UnregisterTask(this);
}

void Wrist::SetPower(double power) {
    m_wristState = WristState::manualVoltage;
    m_wristMotor->Set(ControlMode::PercentOutput, power);
}

void Wrist::SetPosition(double position) {
    m_wristState = WristState::motionMagic;
    int position_clicks = DegreesToNativeUnits(Util::bound(
        position, WRIST_REVERSE_SOFT_LIMIT, WRIST_FORWARD_SOFT_LIMIT));
    m_wristMotor->Set(ControlMode::MotionMagic, position_clicks);
}

void Wrist::SetPositionStep(double position) {
    m_wristState = WristState::motionMagic;
    int position_clicks = DegreesToNativeUnits(Util::bound(
        position, WRIST_REVERSE_SOFT_LIMIT, WRIST_FORWARD_SOFT_LIMIT));
    m_wristMotor->Set(ControlMode::Position, position_clicks);
}

float Wrist::GetPosition() const {
    return NativeUnitsToDegrees(m_wristMotor->GetSelectedSensorPosition(0));
}

void Wrist::ZeroPosition() {
    m_wristMotor->SetSelectedSensorPosition(DegreesToNativeUnits(EXTENDED - 10),
                                            0, 0);
}

void Wrist::OpenClaw() {
    m_cubeClamp->Set(true);
    m_leftRoller->Set(ControlMode::PercentOutput, 0.0);
    m_rightRoller->Set(ControlMode::PercentOutput, 0.0);
}

void Wrist::CloseClaw() {
    m_cubeClamp->Set(false);
}

void Wrist::IntakeCube(double power) {
    m_leftRoller->Set(ControlMode::PercentOutput, power);
    m_rightRoller->Set(ControlMode::PercentOutput, power * 0.8);
}

void Wrist::EjectCube() {
    m_leftRoller->Set(ControlMode::PercentOutput, 1.0);
    m_rightRoller->Set(ControlMode::PercentOutput, 1.0);
}

void Wrist::StopIntake() {
    m_leftRoller->Set(ControlMode::PercentOutput, -0.2);
    m_rightRoller->Set(ControlMode::PercentOutput, -0.2);
}

bool Wrist::IsCubeIn() const {
    return (!m_leftCubeSensor->Get() || !m_rightCubeSensor->Get());
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
    DBStringPrintf(DBStringPos::DB_LINE5, "cube: l%d r %d c%d",
                   m_leftCubeSensor->Get(), m_rightCubeSensor->Get(),
                   IsCubeIn());

    if (m_wristMotor->GetSensorCollection().IsFwdLimitSwitchClosed()) {
        ZeroPosition();
    }

    switch (m_wristState) {
        case WristState::manualVoltage:
            break;
        case WristState::motionMagic:
            break;
        case WristState::manualPosition:
            m_wristMotor->Set(ControlMode::Position,
                              m_wristPositionDelta + this->GetPosition());
            break;
        default:
            break;
    }
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
