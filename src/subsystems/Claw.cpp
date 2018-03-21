#include "src/subsystems/Claw.h"
#include "lib/util/WrapDash.h"

using namespace frc;

namespace frc973 {
Claw::Claw(TaskMgr *scheduler, LogSpreadsheet *logger, DigitalInput *cubeSensor,
           Solenoid *cubeClamp, TalonSRX *leftRoller, TalonSRX *rightRoller)
        : m_scheduler(scheduler)
        , m_cubeSensor(cubeSensor)
        , m_cubeClamp(cubeClamp)
        , m_leftRoller(leftRoller)
        , m_rightRoller(rightRoller) {
    this->m_scheduler->RegisterTask("Claw", this, TASK_PERIODIC);
    m_leftRoller->SetNeutralMode(NeutralMode::Brake);

    m_rightRoller->SetNeutralMode(NeutralMode::Brake);
    m_rightRoller->SetInverted(true);

    m_leftRoller->Set(ControlMode::PercentOutput, 0.0);
    m_rightRoller->Set(ControlMode::PercentOutput, 0.0);
}

Claw::~Claw() {
    m_scheduler->UnregisterTask(this);
}

void Claw::OpenClaw() {
    m_cubeClamp->Set(clawOpen);
}

void Claw::CloseClaw() {
    m_cubeClamp->Set(clawClosed);
}

void Claw::IntakeCube() {
    m_leftRoller->Set(ControlMode::PercentOutput, 1.0);
    m_rightRoller->Set(ControlMode::PercentOutput, 1.0);
}

void Claw::EjectCube() {
    m_leftRoller->Set(ControlMode::PercentOutput, -1.0);
    m_rightRoller->Set(ControlMode::PercentOutput, -1.0);
}

bool Claw::IsCubeIn() {
    return m_cubeSensor->Get();
}

void Claw::TaskPeriodic(RobotMode mode) {
}
}
