#include "src/subsystems/Elevator.h"

using namespace frc;

namespace frc973 {
    Elevator::Elevator(TaskMgr *scheduler, LogSpreadsheet *logger)
    : m_scheduler(scheduler)
    , m_elevatorMotor(new CANTalon(ELEVATOR_CAN_ID))
    , m_position(0.0)
    , m_currLevel(Level::zero)
    , m_talonMode(motorcontrol::ControlMode::PercentOutput)
    {
        this->m_scheduler->RegisterTask("Elevator", this, TASK_PERIODIC);

        m_elevatorMotor->SetFeedbackDevice(CANTalon::FeedbackDevice::CtreMagEncoder_Relative);
        m_elevatorMotor->SetSensorDirection(false);
        m_elevatorMotor->ConfigNominalOutputVoltage(0.0, 0.0);
        m_elevatorMotor->ConfigPeakOutputVoltage(12.0, -12.0);

        m_elevatorMotor->SelectProfileSlot(0);
        m_elevatorMotor->SetP(0.05);
        m_elevatorMotor->SetI(0.0);
        m_elevatorMotor->SetD(0.0);
        m_elevatorMotor->SetF(0.005);
        m_elevatorMotor->SetMotionMagicCruiseVelocity(100.0);
        m_elevatorMotor->SetMotionMagicAcceleration(50.0);
        m_elevatorMotor->SetControlMode(ControlMode::PercentOutput);
        m_positionCell = new LogCell("Elevator Position", 32, true);
        logger->RegisterCell(m_positionCell);
    }

    virtual Elevator::~Elevator() {
        m_scheduler->UnregisterTask(this);
    }

    void Elevator::SetControlMode(ControlMode mode) {
        m_elevatorMotor->motorcontrol::SetControlMode(mode);
        m_talonMode = mode;
    }

    void Elevator::SetPosition(double position) {
        Elevator::SetControlMode(ControlMode::Position);
        m_elevatorMotor->Set(position);
    }

    void Elevator::SetPower(double power) {
        Elevator::SetControlMode(ControlMode::PercentOutput);
        m_elevatorMotor->Set(power);
    }

    void Elevator::SetMotionMagic(double position) {
        Elevator::SetControlMode(ControlMode::MotionMagic);
        m_elevatorMotor->Set(position);
    }

    void Elevator::SetLevel(Level level) {
        m_currLevel = level;
    }

    void Elevator::Reset() {
        SetLevel(Level::zero);
        m_talonMode = ControlMode::PercentOutput;
    }

    void Elevator::TaskPeriodic(RobotMode mode) {
        m_position->LogDouble(m_elevatorMotor->GetPosition());
        switch (m_currLevel) {
          case zero:
              this->SetMotionMagic(0.0);
              break;
          case vault:
              this->SetMotionMagic(3.0);
              break;
          case switch:
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
