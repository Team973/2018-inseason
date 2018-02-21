#include "src/subsystems/Elevator.h"
#include "WPILib.h"
#include "ctre/Phoenix.h"
#include "lib/util/WrapDash.h"

using namespace frc;

namespace frc973 {
Elevator::Elevator(TaskMgr *scheduler, LogSpreadsheet *logger, TalonSRX *motor)
        : m_scheduler(scheduler)
        , m_elevatorMotor(motor)
        , m_position(0.0)
        , m_zeroingTime(0)
        , m_elevatorState(ElevatorState::manual) {
    this->m_scheduler->RegisterTask("Elevator", this, TASK_PERIODIC);

    m_elevatorMotor->ConfigSelectedFeedbackSensor(
        ctre::phoenix::motorcontrol::FeedbackDevice::QuadEncoder, 0,
        10);  // 0 = Not cascaded PID Loop; 10 = in constructor, not in a loop
    m_elevatorMotor->SetSensorPhase(true);
    m_elevatorMotor->SetNeutralMode(NeutralMode::Coast);
    m_elevatorMotor->SetInverted(true);

    m_elevatorMotor->Config_kP(0, 1.5, 10);
    m_elevatorMotor->Config_kI(0, 0.0, 10);
    m_elevatorMotor->Config_kD(0, 0.0, 10);
    m_elevatorMotor->Config_kF(0, 0.0, 10);
    m_elevatorMotor->ConfigMotionCruiseVelocity(3750.0, 10);
    m_elevatorMotor->ConfigMotionAcceleration(4200.0, 10);
    m_elevatorMotor->SelectProfileSlot(0, 0);

    m_elevatorMotor->EnableCurrentLimit(true);
    m_elevatorMotor->ConfigPeakCurrentDuration(0, 10);
    m_elevatorMotor->ConfigPeakCurrentLimit(0, 10);
    m_elevatorMotor->ConfigContinuousCurrentLimit(15, 10);
    m_elevatorMotor->EnableVoltageCompensation(false);
    m_elevatorMotor->ConfigForwardSoftLimitThreshold(
        ELEVATOR_SOFT_HEIGHT_LIMIT / ELEVATOR_INCHES_PER_CLICK, 10);
    m_elevatorMotor->ConfigForwardSoftLimitEnable(true, 10);

    m_elevatorMotor->Set(ControlMode::PercentOutput, 0.0);
    m_positionCell = new LogCell("Elevator Position", 32, true);
    logger->RegisterCell(m_positionCell);
}

Elevator::~Elevator() {
    m_scheduler->UnregisterTask(this);
}

void Elevator::SetPower(double power) {
    m_elevatorState = ElevatorState::manual;
    m_elevatorMotor->Set(ControlMode::PercentOutput, power);
}

void Elevator::SetPosition(double position) {
    m_elevatorState = ElevatorState::position;
    int position_clicks = position / ELEVATOR_INCHES_PER_CLICK;
    m_elevatorMotor->Set(ControlMode::MotionMagic, position_clicks);
}

void Elevator::Reset() {
    m_elevatorState = ElevatorState::zeroing_start;
}

float Elevator::GetPosition() {
    return ELEVATOR_INCHES_PER_CLICK *
           ((float)m_elevatorMotor->GetSelectedSensorPosition(0));
}

void Elevator::ZeroPosition() {
    m_elevatorMotor->GetSensorCollection().SetQuadraturePosition(0, 0);
}

void Elevator::TaskPeriodic(RobotMode mode) {
    m_positionCell->LogDouble(GetPosition());
    SmartDashboard::PutNumber("elevator/encoders/encoder", GetPosition());
    DBStringPrintf(DBStringPos::DB_LINE0, "e %f", GetPosition());
    switch (m_elevatorState) {
        case manual:
            break;
        case zeroing_start:
            m_elevatorState = ElevatorState::zeroing_goDown;
            break;
        case zeroing_goDown:
            m_elevatorMotor->Set(ControlMode::PercentOutput, -0.2);
            break;
        case position:
            break;
        default:
            break;
    }
}
}
