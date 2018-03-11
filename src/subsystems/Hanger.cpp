#include "src/subsystems/Hanger.h"

using namespace frc;

namespace frc973 {
Hanger::Hanger(TaskMgr *scheduler, LogSpreadsheet *logger, Drive *drive,
               Elevator *elevator, Solenoid *hangerPTO, TalonSRX *forkliftTalon,
               UsbCamera intakeCamera, UsbCamera forkCamera, VideoSink greyCam)
        : m_scheduler(scheduler)
        , m_logger(logger)
        , m_drive(drive)
        , m_elevator(elevator)
        , m_hangerPTO(hangerPTO)
        , m_forkliftTalon(forkliftTalon)
        , m_intakeCamera(intakeCamera)
        , m_forkCamera(forkCamera)
        , m_greyCam(greyCam) {
    this->m_scheduler->RegisterTask("Hanger", this, TASK_PERIODIC);

    m_forkliftTalon->SetNeutralMode(NeutralMode::Brake);
}

Hanger::~Hanger() {
    m_scheduler->UnregisterTask(this);
}

void Hanger::EngagePTO() {
    m_hangerPTO->Set(true);
    printf("Setting fork camera\n");
    m_greyCam.SetSource(m_forkCamera);
}

void Hanger::DisengagePTO() {
    m_hangerPTO->Set(false);
    printf("Setting intake camera\n");
    m_greyCam.SetSource(m_intakeCamera);
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
