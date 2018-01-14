#include "src/subsystems/Elevator.h"
#include "WPILib.h"
#include "ctre/Phoenix.h"

using namespace frc;

namespace frc973 {
Elevator::Elevator(TaskMgr *scheduler, LogSpreadsheet *logger, ObservableJoystick *driver)
    : m_scheduler(scheduler)
    , m_elevatorMotor(new TalonSRX(ELEVATOR_CAN_ID))
    , m_position(0.0)
    , m_currLevel(Level::zero)
    , m_talonMode(motorcontrol::ControlMode::PercentOutput)
    , m_joystick(driver)
{
    this->m_scheduler->RegisterTask("Elevator", this, TASK_PERIODIC);

    m_elevatorMotor->ConfigSelectedFeedbackSensor(ctre::phoenix::motorcontrol::FeedbackDevice::QuadEncoder, 0, 10); //0 = Not cascaded PID Loop; 10 = in constructor, not in a loop
    m_elevatorMotor->SetSensorPhase(false);

    m_elevatorMotor->ConfigNominalOutputForward(0.0, 10);
    m_elevatorMotor->ConfigNominalOutputReverse(0.0, 10);
    m_elevatorMotor->ConfigPeakOutputForward(1.0, 10);
    m_elevatorMotor->ConfigPeakOutputReverse(-1.0, 10);

    m_elevatorMotor->Config_kP(0, 0.05, 10);
    m_elevatorMotor->Config_kI(0, 0.0, 10);
    m_elevatorMotor->Config_kD(0, 0.0, 10);
    m_elevatorMotor->Config_kF(0, 0.005,10);
    m_elevatorMotor->ConfigMotionCruiseVelocity(100.0, 10);
    m_elevatorMotor->ConfigMotionAcceleration(50.0, 10);

    m_elevatorMotor->Set(ControlMode::PercentOutput, 0.0);
    m_positionCell = new LogCell("Elevator Position", 32, true);
    logger->RegisterCell(m_positionCell);
}

Elevator::~Elevator() {
    m_scheduler->UnregisterTask(this);
}

void Elevator::SetControlMode(ControlMode mode, double value) {
    m_elevatorMotor->Set(mode, value);
    m_talonMode = mode;
}

void Elevator::SetPosition(double position) {
    this->SetControlMode(ControlMode::Position, position);
}

void Elevator::SetPower(double power) {
    m_elevatorMotor->Set(ControlMode::PercentOutput, power);
}

void Elevator::SetMotionMagic(double position) {
    Elevator::SetControlMode(ControlMode::MotionMagic, position);
}

void Elevator::SetLevel(Level level) {
    m_currLevel = level;
}

void Elevator::Reset() {
    SetLevel(Level::zero);
    m_talonMode = ControlMode::PercentOutput;
}

void Elevator::TaskPeriodic(RobotMode mode) {
    m_positionCell->LogDouble(m_elevatorMotor->GetSelectedSensorPosition(0));
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
