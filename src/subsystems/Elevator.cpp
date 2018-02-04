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
        , m_elevatorState(ElevatorState::manual) {
    this->m_scheduler->RegisterTask("Elevator", this, TASK_PERIODIC);

    m_elevatorMotor->ConfigSelectedFeedbackSensor(
        ctre::phoenix::motorcontrol::FeedbackDevice::QuadEncoder, 0,
        10);  // 0 = Not cascaded PID Loop; 10 = in constructor, not in a loop
    m_elevatorMotor->SetSensorPhase(true);
    m_elevatorMotor->SetNeutralMode(NeutralMode::Brake);
    m_elevatorMotor->SetInverted(true);

    m_elevatorMotor->Config_kP(0, 1.5, 10);
    m_elevatorMotor->Config_kI(0, 0.0, 10);
    m_elevatorMotor->Config_kD(0, 0.0, 10);
    m_elevatorMotor->Config_kF(0, 0.0, 10);
    m_elevatorMotor->ConfigMotionCruiseVelocity(3000.0, 10);
    m_elevatorMotor->ConfigMotionAcceleration(2000.0, 10);
    m_elevatorMotor->SelectProfileSlot(0, 0);

    m_elevatorMotor->EnableCurrentLimit(true);
    m_elevatorMotor->ConfigPeakCurrentDuration(0, 10);
    m_elevatorMotor->ConfigPeakCurrentLimit(0, 10);
    m_elevatorMotor->ConfigContinuousCurrentLimit(5, 10);
    m_elevatorMotor->EnableVoltageCompensation(false);

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
    m_elevatorState = ElevatorState::zeroing;
}

float Elevator::GetPosition() {
    return ELEVATOR_INCHES_PER_CLICK *
           ((float)m_elevatorMotor->GetSelectedSensorPosition(0));
}

void Elevator::TaskPeriodic(RobotMode mode) {
    m_positionCell->LogDouble(GetPosition());
    printf("Elevator Pos: %f\n", GetPosition());
    SmartDashboard::PutNumber("/SmartDashboard/elevator/currents/current", m_elevatorMotor->GetOutputCurrent());
    DBStringPrintf(DBStringPos::DB_LINE4, "%f", GetPosition());
    switch (m_elevatorState) {
        case manual:
            break;
        case zeroing:
            m_elevatorState = ElevatorState::goDown;
            break;
        case goDown:
            this->SetPower(-0.2);
            if (m_elevatorMotor->GetOutputCurrent() > 4.0) {
                m_elevatorState = ElevatorState::stop;
            }
            break;
        case stop:
            m_elevatorMotor->GetSensorCollection().SetQuadraturePosition(0,0);
            this->SetPower(0.0);
            m_elevatorState = ElevatorState::manual;
            break;
        case position:
            break;
        default:
            break;
        }
    }
}
