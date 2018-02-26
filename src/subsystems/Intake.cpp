
#include <stdio.h>
#include "src/subsystems/Intake.h"
#include "lib/util/WrapDash.h"

using namespace frc;

namespace frc973 {
Intake::Intake(TaskMgr *scheduler, LogSpreadsheet *logger, TalonSRX *leftRoller,
               TalonSRX *rightRoller, DigitalInput *cubeSensor,
               Solenoid *position, Solenoid *openClose)
        : m_scheduler(scheduler)
        , m_leftRoller(leftRoller)
        , m_rightRoller(rightRoller)
        , m_cubeSensor(cubeSensor)
        , m_position(position)
        , m_openClose(openClose)
        , m_intakeState(IntakeState::Idle) {
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
    m_intakeState = IntakeState::Intaking;
}

void Intake::RegularPull() {
    m_intakeState = IntakeState::Idle;
    m_leftRoller->Set(ControlMode::PercentOutput, 0.4);
    m_rightRoller->Set(ControlMode::PercentOutput, 0.8);
}

void Intake::Eject() {
    m_intakeState = IntakeState::Idle;
    printf("Ejecting\n");
    m_leftRoller->Set(ControlMode::PercentOutput, -1.0);
    m_rightRoller->Set(ControlMode::PercentOutput, -1.0);
}

void Intake::Stop() {
    m_intakeState = IntakeState::Idle;
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

void Intake::Open() {
    m_openClose->Set(true);
}

void Intake::Close() {
    m_openClose->Set(false);
}

void Intake::SpinCube(int direction) {
    m_intakeState = IntakeState::Idle;
    if (direction < 0) {
        m_leftRoller->Set(ControlMode::PercentOutput, -0.3);
        m_rightRoller->Set(ControlMode::PercentOutput, 0.6);
    }
    else if (direction > 0) {
        m_leftRoller->Set(ControlMode::PercentOutput, 0.6);
        m_rightRoller->Set(ControlMode::PercentOutput, -0.3);
    }
    else {
        m_leftRoller->Set(ControlMode::PercentOutput, 0.0);
        m_rightRoller->Set(ControlMode::PercentOutput, 0.0);
    }
}

void Intake::TaskPeriodic(RobotMode mode) {
    SmartDashboard::PutBoolean("intake/sensors/bannersensor", IsCubeIn());
    DBStringPrintf(DB_LINE1, "ric %.2lf lif %.2lf",
                   m_rightRoller->GetOutputCurrent(),
                   m_leftRoller->GetOutputCurrent());
    switch (m_intakeState) {
        case IntakeState::Idle:
            break;
        case IntakeState::Intaking:
            if (IsCubeIn()) {
                m_intakeState = IntakeState::Idle;
                m_leftRoller->Set(ControlMode::PercentOutput, 0.0);
                m_rightRoller->Set(ControlMode::PercentOutput, 0.0);
            }
            else {
                m_leftRoller->Set(ControlMode::PercentOutput, 0.5);
                m_rightRoller->Set(ControlMode::PercentOutput, 0.9);
            }
            break;
    }
    printf("cubeS %d\n", IsCubeIn());
}
}
