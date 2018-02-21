#include "src/subsystems/Hanger.h"

using namespace frc;

namespace frc973 {
Hanger::Hanger(TaskMgr *scheduler, LogSpreadsheet *logger, Drive *drive,
               Elevator *elevator, Solenoid *hangerPTO, TalonSRX *forkliftTalon)
        : m_scheduler(scheduler)
        , m_logger(logger)
        , m_drive(drive)
        , m_elevator(elevator)
        , m_hangerPTO(hangerPTO)
        , m_forkliftTalon(forkliftTalon) {
    this->m_scheduler->RegisterTask("Hanger", this, TASK_PERIODIC);

    m_forkliftTalon->SetNeutralMode(NeutralMode::Brake);
}

Hanger::~Hanger() {
    m_scheduler->UnregisterTask(this);
}

void Hanger::EngagePTO() {
    m_hangerPTO->Set(true);
}

void Hanger::DisengagePTO() {
    m_hangerPTO->Set(false);
}

void Hanger::SetForkliftPower(double power) {
    m_forkliftTalon->Set(ControlMode::PercentOutput, power);
}

void Hanger::SetHangerPower(double power) {
    this->EngagePTO();
    m_drive->HangerDrive(power);
}

void Hanger::TaskPeriodic(RobotMode mode) {
}
}
