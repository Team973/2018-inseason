#include "src/subsystems/Claw.h"

using namespace frc;

namespace frc973 {
Claw::Claw(TaskMgr *scheduler, LogSpreadsheet *logger,
           TalonSRX *leftRoller, TalonSRX *rightRoller,
           DigitalInput *cubeSensor)
    : m_scheduler(scheduler)
    , m_leftRoller(leftRoller)
    , m_rightRoller(rightRoller)
    , m_cubeSensor(cubeSensor)
{
    this->m_scheduler->RegisterTask("Claw", this, TASK_PERIODIC);
    m_leftRoller->SetNeutralMode(NeutralMode::Brake);

    m_leftRoller->ConfigNominalOutputForward(0.0, 10);
    m_leftRoller->ConfigNominalOutputReverse(0.0, 10);
    m_leftRoller->ConfigPeakOutputForward(1.0, 10);
    m_leftRoller->ConfigPeakOutputReverse(-1.0, 10);

    m_rightRoller->SetNeutralMode(NeutralMode::Brake);
    m_rightRoller->SetInverted(true);

    m_rightRoller->ConfigNominalOutputForward(0.0, 10);
    m_rightRoller->ConfigNominalOutputReverse(0.0, 10);
    m_rightRoller->ConfigPeakOutputForward(1.0, 10);
    m_rightRoller->ConfigPeakOutputReverse(-1.0, 10);

    m_leftRoller->Set(ControlMode::PercentOutput, 0.0);
    m_rightRoller->Set(ControlMode::PercentOutput, 0.0);
}

Claw::~Claw() {
    m_scheduler->UnregisterTask(this);
}

void Claw::Intake() {
  if (m_cubeSensor->Get() == false) {
      m_leftRoller->Set(ControlMode::PercentOutput, 1.0);
      m_rightRoller->Set(ControlMode::PercentOutput, 1.0);
  }
  else {
      m_leftRoller->Set(ControlMode::PercentOutput, 0.0);
      m_rightRoller->Set(ControlMode::PercentOutput, 0.0);
  }
}

void Claw::Eject() {
    m_leftRoller->Set(ControlMode::PercentOutput, -1.0);
    m_rightRoller->Set(ControlMode::PercentOutput, -1.0);
}

void Claw::Stop() {
    m_leftRoller->Set(ControlMode::PercentOutput, 0.0);
    m_rightRoller->Set(ControlMode::PercentOutput, 0.0);
}

bool Claw::IsCubeIn() {
    return m_cubeSensor->Get();
}

void Claw::TaskPeriodic(RobotMode mode) {
}
}
