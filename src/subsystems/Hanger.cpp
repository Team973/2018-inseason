#include "src/subsystems/Hanger.h"

using namespace frc;

namespace frc973 {
Hanger::Hanger(TaskMgr *scheduler, LogSpreadsheet *logger, Drive *drive,
               Elevator *elevator, Solenoid *hangerpto)
        : m_scheduler(scheduler)
        , m_logger(logger)
        , m_drive(drive)
        , m_elevator(elevator)
        , m_hangerpto(hangerpto) {
    this->m_scheduler->RegisterTask("Hanger", this, TASK_PERIODIC);
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

void Hanger::TaskPeriodic(RobotMode mode) {
}
}
