#include "src/subsystems/Hanger.h"

using namespace frc;

namespace frc973 {
Hanger::Hanger(TaskMgr *scheduler, LogSpreadsheet *logger, Drive *drive,
               Elevator *elevator, Solenoid *hangerpto, TalonSRX *forkliftTalon,
               VictorSPX *forkliftVictor)
        : m_scheduler(scheduler)
        , m_logger(logger)
        , m_drive(drive)
        , m_elevator(elevator)
        , m_hangerpto(hangerpto)
        , m_forkliftTalon(forkliftTalon)
        , m_forkliftVictor(forkliftVictor) {
    this->m_scheduler->RegisterTask("Hanger", this, TASK_PERIODIC);

    m_forkliftTalon->SetSensorPhase(false);
    m_forkliftTalon->SetNeutralMode(NeutralMode::Brake);

    m_forkliftTalon->ConfigNominalOutputForward(0.0, 10);
    m_forkliftTalon->ConfigNominalOutputReverse(0.0, 10);
    m_forkliftTalon->ConfigPeakOutputForward(1.0, 10);
    m_forkliftTalon->ConfigPeakOutputReverse(-1.0, 10);

    m_forkliftVictor->Follow(*m_forkliftTalon);
}

Hanger::~Hanger() {
    m_scheduler->UnregisterTask(this);
}
void Hanger::EngagePTO() {
    m_hangerpto->Set(true);
}
void Hanger::DisengagePTO() {
    m_hangerpto->Set(false);
}
void Hanger::ForkliftForwardpower() {
    m_forkliftTalon->Set(ControlMode::PercentOutput, 1.0);
}
void Hanger::ForkliftReversepower() {
    m_forkliftTalon->Set(ControlMode::PercentOutput, -1.0);
}

void Hanger::TaskPeriodic(RobotMode mode) {
}
}
