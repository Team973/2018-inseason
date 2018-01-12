#include "src/subsystems/Elevator.h"
#include "WPILib.h"

using namespace frc;

namespace frc973 {
Elevator::Elevator(TaskMgr *scheduler, LogSpreadsheet *logger)
: m_scheduler(scheduler)
, m_elevatorMotor(new WPI_TalonSRX(ELEVATOR_CAN_ID))
, m_position(0.0)
, m_currLevel(Level::zero)
, m_talonMode(motorcontrol::ControlMode::PercentOutput)
{
    this->m_scheduler->RegisterTask("Elevator", this, TASK_PERIODIC);

    m_elevatorMotor->ConfigSelectedFeedbackSensor(CtreMagEncoder_Relative);
    m_elevatorMotor->SetSensorPhase(false);
    m_elevatorMotor->configPeakOutputForward(0.0, 0.0);
    m_elevatorMotor->configPeakOutputReverse(-1.0, 1.0);

    m_elevatorMotor->config_kP(0.05,20);
    m_elevatorMotor->config_kI(0.0,20);
    m_elevatorMotor->config_kD(0.0,20);
    m_elevatorMotor->config_kF(0.005,20);
    m_elevatorMotor->configMotionCruiseVelocity(100.0);
    m_elevatorMotor->configMotionAcceleration(50.0);
    m_elevatorMotor->changeControlMode(ControlMode::PercentOutput);
    m_positionCell = new LogCell("Elevator Position", 32, true);
    logger->RegisterCell(m_positionCell);
}

Elevator::~Elevator() {
    m_scheduler->UnregisterTask(this);
}

void Elevator::SetControlMode(ControlMode mode) {
    m_elevatorMotor->motorcontrol::changeControlMode(mode);
    m_talonMode = mode;
}

void Elevator::SetPosition(double position) {
    Elevator::SetControlMode(ControlMode::Position);
    m_elevatorMotor->setSelectedSensorPosition(position);
}

void Elevator::SetPower(double power) {
    Elevator::SetControlMode(ControlMode::PercentOutput);
    m_elevatorMotor->Set(power);
}

void Elevator::SetMotionMagic(double position) {
    Elevator::SetControlMode(ControlMode::MotionMagic);
    m_elevatorMotor->setSelectedSensorPosition(position);
}

void Elevator::SetLevel(Level level) {
    m_currLevel = level;
}

void Elevator::Reset() {
    SetLevel(Level::zero);
    m_talonMode = ControlMode::PercentOutput;
}

void Elevator::TaskPeriodic(RobotMode mode) {
    m_positionCell->LogDouble(m_elevatorMotor->getSelectedSensorPosition());
    switch (m_currLevel) {
      case zero:
          this->SetMotionMagic(0.0);
          break;
      case vault:
          this->SetMotionMagic(3.0);
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
          this->SetMotionMagic(70.0);
          break;
      case manual:
          this->Reset();
          break;
      default:
          this->Reset();
          break;
    }
}
}
