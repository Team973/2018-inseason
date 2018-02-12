
#include "src/subsystems/Intake.h"

using namespace frc;

namespace frc973 {
Intake::Intake(TaskMgr *scheduler, LogSpreadsheet *logger, TalonSRX *leftRoller,
               TalonSRX *rightRoller, DigitalInput *cubeSensor,
               Solenoid *position)
        : m_scheduler(scheduler)
        , m_leftRoller(leftRoller)
        , m_rightRoller(rightRoller)
        , m_cubeSensor(cubeSensor)
        , m_position(position) {
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

void Intake::AutomatedPull() {
    if (m_cubeSensor->Get() == false) {
        printf("Intaking\n");
        RegularPull();
    }
    else {
        m_leftRoller->Set(ControlMode::PercentOutput, 0.0);
        m_rightRoller->Set(ControlMode::PercentOutput, 0.0);
    }
}

void Intake::RegularPull() {
    m_leftRoller->Set(ControlMode::PercentOutput,
                      -0.7);  // Negative output will cause intake to intake
    m_rightRoller->Set(ControlMode::PercentOutput, -0.7);
}

void Intake::Eject() {
    printf("Ejecting\n");
    m_leftRoller->Set(ControlMode::PercentOutput,
                      0.7);  // Positive output will cause intake to spit out
    m_rightRoller->Set(ControlMode::PercentOutput, 0.7);
}

void Intake::Stop() {
    m_leftRoller->Set(ControlMode::PercentOutput, 0.0);
    m_rightRoller->Set(ControlMode::PercentOutput, 0.0);
}

bool Intake::IsCubeIn() {
    return m_cubeSensor->Get();
}

void Intake::LowerIntake() {
    m_position->Set(true);
}

void Intake::RaiseIntake() {
    m_position->Set(false);
}

void Intake::TaskPeriodic(RobotMode mode) {
}
}
