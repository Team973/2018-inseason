#include "src/subsystems/Hanger.h"

using namespace frc;

namespace frc973 {
Hanger::Hanger(TaskMgr *scheduler, LogSpreadsheet *logger, Drive *drive,
               Elevator *elevator, Solenoid *hangerpto, TalonSRX *forkliftTalon)
        : m_scheduler(scheduler)
        , m_logger(logger)
        , m_drive(drive)
        , m_elevator(elevator)
        , m_hangerpto(hangerpto)
        , m_forkliftTalon(forkliftTalon) {
    this->m_scheduler->RegisterTask("Hanger", this, TASK_PERIODIC);

    m_forkliftTalon->SetNeutralMode(NeutralMode::Brake);
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
void Hanger::SetForkliftPower(double power) {
    m_forkliftTalon->Set(ControlMode::PercentOutput, power);
}

void Hanger::TaskPeriodic(RobotMode mode) {
}
}
