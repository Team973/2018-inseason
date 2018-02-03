#include "src/subsystems/Elevator.h"
#include "WPILib.h"
#include "ctre/Phoenix.h"

using namespace frc;

namespace frc973 {
Elevator::Elevator(TaskMgr *scheduler, LogSpreadsheet *logger,
                   TalonSRX *motor)
        : m_scheduler(scheduler)
        , m_elevatorMotor(motor)
        , m_position(0.0)
        , m_currLevel(Level::zero)
        , m_talonMode(TalonMode::manual){
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
    m_elevatorMotor->ConfigMotionCruiseVelocity(1000.0, 10);
    m_elevatorMotor->ConfigMotionAcceleration(1000.0, 10);
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

void Elevator::SetControlMode(ControlMode mode, double value) {
    m_elevatorMotor->Set(mode, value);
}

void Elevator::SetPower(double power) {
    m_elevatorMotor->Set(ControlMode::PercentOutput, power);
    m_talonMode = TalonMode::manual;
}

void Elevator::SetMotionMagic(double position) {
    Elevator::SetControlMode(ControlMode::MotionMagic, position);
    m_talonMode = TalonMode::motionMagic;
}

void Elevator::SetLevel(Level level) {
    m_currLevel = level;
    m_talonMode = TalonMode::motionMagic;
}

void Elevator::Reset() {
    m_currLevel = Level::zero;
}

int Elevator::GetPosition() {
    return m_elevatorMotor->GetSelectedSensorPosition(0);
}

void Elevator::TaskPeriodic(RobotMode mode) {
    m_positionCell->LogDouble(GetPosition());
    printf("Elevator Pos: %d\n", m_elevatorMotor->GetSelectedSensorPosition(0));
    SmartDashboard::PutNumber("elevator/current", m_elevatorMotor->GetOutputCurrent());
    /*switch (m_talonMode) {
        case manual:
            break;
        case motionMagic:
            switch (m_currLevel) {
                case zero:
                    this->SetPower(-0.2);
                    if (m_elevatorMotor->GetOutputCurrent() > 4.0) {
                        m_elevatorMotor->GetSensorCollection().SetQuadraturePosition(0, 0);
                        this->SetPower(0.0);
                        m_currLevel = Level::lowGoal;
                    }
                    break;
                case lowGoal:
                    this->SetMotionMagic(30.0);
                    break;
                case scaleLow:
                    this->SetMotionMagic(50.0);
                    break;
                case scaleMid:
                    this->SetMotionMagic(60.0);
                    break;
                case scaleHigh:
                    this->SetMotionMagic(1000.0);
                    break;
                default:
                    this->Reset();
                    break;
            }
          break;
      default:
          break;
    }*/
}
}
