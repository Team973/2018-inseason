
#include "src/subsystems/Intake.h"

using namespace frc;

namespace frc973 {
Intake::Intake(TaskMgr *scheduler, LogSpreadsheet *logger, TalonSRX *leftRoller,
               TalonSRX *rightRoller, DigitalInput *cubeSensor)
        : m_scheduler(scheduler)
        , m_leftRoller(leftRoller)
        , m_rightRoller(rightRoller)
        , m_cubeSensor(cubeSensor) {
    this->m_scheduler->RegisterTask("Intake", this, TASK_PERIODIC);
    m_leftRoller->SetNeutralMode(NeutralMode::Brake);

    m_rightRoller->SetNeutralMode(NeutralMode::Brake);
    m_rightRoller->SetInverted(true);

    m_leftRoller->Set(ControlMode::PercentOutput, 0.0);
    m_rightRoller->Set(ControlMode::PercentOutput, 0.0);
}

Intake::~Intake() {
    m_scheduler->UnregisterTask(this);
}

void Intake::Pull() {
    if (m_cubeSensor->Get() == false) {
        m_leftRoller->Set(ControlMode::PercentOutput, 1.0);
        m_rightRoller->Set(ControlMode::PercentOutput, 1.0);
    }
    else {
        m_leftRoller->Set(ControlMode::PercentOutput, 0.0);
        m_rightRoller->Set(ControlMode::PercentOutput, 0.0);
    }
}

void Intake::Eject() {
    m_leftRoller->Set(ControlMode::PercentOutput, -1.0);
    m_rightRoller->Set(ControlMode::PercentOutput, -1.0);
}

void Intake::Stop() {
    m_leftRoller->Set(ControlMode::PercentOutput, 0.0);
    m_rightRoller->Set(ControlMode::PercentOutput, 0.0);
}

bool Intake::IsCubeIn() {
    return m_cubeSensor->Get();
}

void Intake::TaskPeriodic(RobotMode mode) {
}
}
