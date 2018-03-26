#include "src/subsystems/Wrist.h"
#include "WPILib.h"
#include "ctre/Phoenix.h"
#include "lib/util/WrapDash.h"

using namespace frc;

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
        ctre::phoenix::motorcontrol::FeedbackDevice::QuadEncoder, 0,
        10);  // 0 = Not cascaded PID Loop; 10 = in constructor, not in a loop
    m_wristMotor->SetSensorPhase(true);
    m_wristMotor->SetNeutralMode(NeutralMode::Coast);
    m_wristMotor->SetInverted(true);

    m_wristMotor->Config_kP(0, 3.0, 10);
    m_wristMotor->Config_kI(0, 0.0, 10);
    m_wristMotor->Config_kD(0, 0.0, 10);
    m_wristMotor->Config_kF(0, 0.0, 10);
    m_wristMotor->ConfigMotionCruiseVelocity(3750.0, 10);
    m_wristMotor->ConfigMotionAcceleration(4200.0, 10);
    m_wristMotor->SelectProfileSlot(0, 0);

    m_wristMotor->EnableCurrentLimit(true);
    m_wristMotor->ConfigPeakCurrentDuration(0, 10);
    m_wristMotor->ConfigPeakCurrentLimit(0, 10);
    m_wristMotor->ConfigContinuousCurrentLimit(15, 10);
    m_wristMotor->ConfigPeakOutputForward(0.5, 10);
    m_wristMotor->ConfigPeakOutputReverse(-0.5, 10);

    /*if (this->GetPosition() > 180.0) {
        m_wristMotor->GetSensorCollection().SetQuadraturePosition(
            (int)((this->GetPosition() - 360) / WRIST_DEGREES_PER_CLICK), 10);
    }*/
    ZeroPosition();

    m_wristMotor->ConfigForwardSoftLimitThreshold(
        WRIST_FORWARD_SOFT_LIMIT / WRIST_DEGREES_PER_CLICK, 10);
    m_wristMotor->ConfigForwardSoftLimitEnable(true, 10);

    m_wristMotor->ConfigReverseSoftLimitThreshold(
        WRIST_REVERSE_SOFT_LIMIT / WRIST_DEGREES_PER_CLICK, 10);
    m_wristMotor->ConfigReverseSoftLimitEnable(true, 10);

    m_wristMotor->Set(ControlMode::PercentOutput, 0.0);

    m_leftRoller->SetNeutralMode(NeutralMode::Brake);

    m_rightRoller->SetNeutralMode(NeutralMode::Brake);
    m_rightRoller->SetInverted(true);

    m_leftRoller->Set(ControlMode::PercentOutput, 0.0);
    m_rightRoller->Set(ControlMode::PercentOutput, 0.0);

    m_leftRoller->EnableCurrentLimit(true);
    m_leftRoller->ConfigPeakCurrentDuration(0, 10);
    m_leftRoller->ConfigPeakCurrentLimit(0, 10);
    m_leftRoller->ConfigContinuousCurrentLimit(15, 10);

    m_rightRoller->EnableCurrentLimit(true);
    m_rightRoller->ConfigPeakCurrentDuration(0, 10);
    m_rightRoller->ConfigPeakCurrentLimit(0, 10);
    m_rightRoller->ConfigContinuousCurrentLimit(15, 10);

    m_bannerFilter->Add(m_leftCubeSensor);
    m_bannerFilter->Add(m_rightCubeSensor);
    m_bannerFilter->SetPeriodNanoSeconds(10000);
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
    int position_clicks = Util::bound(position, WRIST_REVERSE_SOFT_LIMIT,
                                      WRIST_FORWARD_SOFT_LIMIT) /
                          WRIST_DEGREES_PER_CLICK;
    m_wristMotor->Set(ControlMode::MotionMagic, position_clicks);
}

void Wrist::SetPositionStep(double position) {
    m_wristState = WristState::motionMagic;
    int position_clicks = Util::bound(position, WRIST_REVERSE_SOFT_LIMIT,
                                      WRIST_FORWARD_SOFT_LIMIT) /
                          WRIST_DEGREES_PER_CLICK;
    m_wristMotor->Set(ControlMode::Position, position_clicks);
}

float Wrist::GetPosition() {
    return WRIST_DEGREES_PER_CLICK *
           ((float)m_wristMotor->GetSelectedSensorPosition(0));
}

void Wrist::ZeroPosition() {
    m_wristMotor->GetSensorCollection().SetQuadraturePosition(
        90.0 / WRIST_DEGREES_PER_CLICK, 0);
}

void Wrist::OpenClaw() {
    m_cubeClamp->Set(true);
}

void Wrist::CloseClaw() {
    m_cubeClamp->Set(false);
}

void Wrist::IntakeCube(double power) {
    m_leftRoller->Set(ControlMode::PercentOutput, power);
    m_rightRoller->Set(ControlMode::PercentOutput, power);
}

void Wrist::EjectCube() {
    m_leftRoller->Set(ControlMode::PercentOutput, 1.0);
    m_rightRoller->Set(ControlMode::PercentOutput, 1.0);
}

void Wrist::StopIntake() {
    m_leftRoller->Set(ControlMode::PercentOutput, -0.1);
    m_rightRoller->Set(ControlMode::PercentOutput, -0.1);
}

bool Wrist::IsCubeIn() {
    return (!m_leftCubeSensor->Get() || !m_rightCubeSensor->Get());
}

void Wrist::TaskPeriodic(RobotMode mode) {
    SmartDashboard::PutNumber("elevator/encoders/encoder", GetPosition());
    DBStringPrintf(DBStringPos::DB_LINE7, "e %d",
                   m_wristMotor->GetClosedLoopError(0));
    DBStringPrintf(DBStringPos::DB_LINE5, "cube: l%d r %d c%d",
                   m_leftCubeSensor->Get(), m_rightCubeSensor->Get(),
                   IsCubeIn());
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
}
