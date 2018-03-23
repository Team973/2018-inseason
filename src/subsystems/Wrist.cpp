#include "src/subsystems/Wrist.h"
#include "WPILib.h"
#include "ctre/Phoenix.h"
#include "lib/util/WrapDash.h"

using namespace frc;

namespace frc973 {
Wrist::Wrist(TaskMgr *scheduler, LogSpreadsheet *logger,
             DigitalInput *cubeSensor, TalonSRX *wristMotor,
             TalonSRX *leftRoller, TalonSRX *rightRoller, Solenoid *cubeClamp)
        : m_scheduler(scheduler)
        , m_wristState(WristState::manualVoltage)
        , m_cubeSensor(cubeSensor)
        , m_cubeClamp(cubeClamp)
        , m_leftRoller(leftRoller)
        , m_rightRoller(rightRoller)
        , m_wristMotor(wristMotor)
        , m_position(0.0)
        , m_prevWristSetpoint(0.0)
        , m_wristPositionDelta(0.0)
        , m_zeroingTime(0) {
    this->m_scheduler->RegisterTask("Wrist", this, TASK_PERIODIC);
    this->m_scheduler->RegisterTask("Claw", this, TASK_PERIODIC);

    m_wristMotor->ConfigSelectedFeedbackSensor(
        ctre::phoenix::motorcontrol::FeedbackDevice::CTRE_MagEncoder_Absolute,
        0,
        10);  // 0 = Not cascaded PID Loop; 10 = in constructor, not in a loop
    m_wristMotor->SetSensorPhase(true);
    m_wristMotor->SetNeutralMode(NeutralMode::Coast);
    m_wristMotor->SetInverted(true);

    m_wristMotor->Config_kP(0, 1.5, 10);
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
    m_wristMotor->EnableVoltageCompensation(false);
    m_wristMotor->ConfigForwardSoftLimitThreshold(
        WRIST_SOFT_LIMIT / WRIST_INCHES_PER_CLICK, 10);
    m_wristMotor->ConfigForwardSoftLimitEnable(true, 10);

    m_wristMotor->Set(ControlMode::PercentOutput, 0.0);

    m_leftRoller->SetNeutralMode(NeutralMode::Brake);

    m_rightRoller->SetNeutralMode(NeutralMode::Brake);
    m_rightRoller->SetInverted(true);

    m_leftRoller->Set(ControlMode::PercentOutput, 0.0);
    m_rightRoller->Set(ControlMode::PercentOutput, 0.0);
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
    int position_clicks = position / WRIST_INCHES_PER_CLICK;
    m_wristMotor->Set(ControlMode::MotionMagic, position_clicks);
}

void Wrist::SetManualInput(double input) {
    m_wristState = WristState::manualPosition;
    m_wristPositionDelta =
        input * WRIST_MAX_SPEED * ROBOT_LOOP_PERIOD_SEC_PER_LOOP +
        m_prevWristSetpoint;
}

float Wrist::GetPosition() {
    return WRIST_INCHES_PER_CLICK *
           ((float)m_wristMotor->GetSelectedSensorPosition(0));
}

void Wrist::ZeroPosition() {
    m_wristMotor->GetSensorCollection().SetQuadraturePosition(0, 0);
}

void Wrist::OpenClaw() {
    m_cubeClamp->Set(true);
}

void Wrist::CloseClaw() {
    m_cubeClamp->Set(false);
}

void Wrist::IntakeCube() {
    m_leftRoller->Set(ControlMode::PercentOutput, 1.0);
    m_rightRoller->Set(ControlMode::PercentOutput, 1.0);
}

void Wrist::EjectCube() {
    m_leftRoller->Set(ControlMode::PercentOutput, -1.0);
    m_rightRoller->Set(ControlMode::PercentOutput, -1.0);
}

void Wrist::StopIntake() {
    m_leftRoller->Set(ControlMode::PercentOutput, 0.0);
    m_rightRoller->Set(ControlMode::PercentOutput, 0.0);
}

bool Wrist::IsCubeIn() {
    return m_cubeSensor->Get();
}

void Wrist::TaskPeriodic(RobotMode mode) {
    SmartDashboard::PutNumber("elevator/encoders/encoder", GetPosition());
    DBStringPrintf(DBStringPos::DB_LINE0, "e %f", GetPosition());
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
