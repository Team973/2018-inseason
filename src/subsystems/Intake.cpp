#include "src/subsystems/Intake.h"
#include "WPILib.h"
#include "ctre/Phoenix.h"
#include "lib/util/WrapDash.h"

using namespace frc;
using namespace ctre::phoenix::motorcontrol;

namespace frc973 {
Intake::Intake(TaskMgr *scheduler, LogSpreadsheet *logger,
               DigitalInput *rightCubeSensor, DigitalInput *leftCubeSensor,
               TalonSRX *leftRoller, TalonSRX *rightRoller, Solenoid *cubeClamp)
        : m_scheduler(scheduler)
        , m_rightCubeSensor(rightCubeSensor)
        , m_leftCubeSensor(leftCubeSensor)
        , m_cubeClamp(cubeClamp)
        , m_leftRoller(leftRoller)
        , m_rightRoller(rightRoller)
        , m_bannerFilter(new DigitalGlitchFilter()) {
    this->m_scheduler->RegisterTask("Intake", this, TASK_PERIODIC);

    m_leftRoller->SetNeutralMode(NeutralMode::Brake);

    m_rightRoller->SetNeutralMode(NeutralMode::Brake);
    m_rightRoller->SetInverted(true);

    m_leftRoller->Set(ControlMode::PercentOutput, 0.0);
    m_rightRoller->Set(ControlMode::PercentOutput, 0.0);

    m_leftRoller->EnableCurrentLimit(true);
    m_leftRoller->ConfigPeakCurrentDuration(0, 10);
    m_leftRoller->ConfigPeakCurrentLimit(0, 10);
    m_leftRoller->ConfigContinuousCurrentLimit(50, 10);

    m_rightRoller->EnableCurrentLimit(true);
    m_rightRoller->ConfigPeakCurrentDuration(0, 10);
    m_rightRoller->ConfigPeakCurrentLimit(0, 10);
    m_rightRoller->ConfigContinuousCurrentLimit(50, 10);

    m_bannerFilter->Add(m_leftCubeSensor);
    m_bannerFilter->Add(m_rightCubeSensor);
    m_bannerFilter->SetPeriodNanoSeconds(80000);
}

Intake::~Intake() {
    m_scheduler->UnregisterTask(this);
}

void Intake::OpenClaw() {
    m_cubeClamp->Set(true);
}

void Intake::CloseClaw() {
    m_cubeClamp->Set(false);
}

void Intake::IntakeCube(double power) {
    m_leftRoller->Set(ControlMode::PercentOutput, power);
    m_rightRoller->Set(ControlMode::PercentOutput, power * 0.8);
}

void Intake::EjectCube(double power) {
    m_leftRoller->Set(ControlMode::PercentOutput, power);
    m_rightRoller->Set(ControlMode::PercentOutput, power);
}

void Intake::HoldCube() {
    m_leftRoller->Set(ControlMode::PercentOutput, -0.15);
    m_rightRoller->Set(ControlMode::PercentOutput, -0.15);
}

void Intake::StopIntake() {
    m_leftRoller->Set(ControlMode::PercentOutput, 0.0);
    m_rightRoller->Set(ControlMode::PercentOutput, 0.0);
}

bool Intake::IsCubeIn() const {
    return (!m_leftCubeSensor->Get() || !m_rightCubeSensor->Get());
}

void Intake::TaskPeriodic(RobotMode mode) {
    DBStringPrintf(DBStringPos::DB_LINE5, "cube: l%d r %d c%d",
                   m_leftCubeSensor->Get(), m_rightCubeSensor->Get(),
                   IsCubeIn());
}
}
