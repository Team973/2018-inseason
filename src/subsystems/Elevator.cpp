#include "src/subsystems/Elevator.h"

using namespace frc;

namespace frc973 {
    Elevator::Elevator(TaskMgr *scheduler, LogSpreadsheet *logger)
    : m_scheduler(scheduler)
    , m_elevatorMotor(new CANTalon(ELEVATOR_CAN_ID))
    , m_position(0.0)
    , m_currLevel(Level::zero)
    {
        m_elevatorMotor->SetControlMode(ControlMode::PercentOutput);
        logger->RegisterCell(m_position);
    }

    virtual Elevator::~Elevator() {
        m_scheduler->UnregisterTask(this);
    }

    void SetPosition(double position) {

    }

    void SetPower(double power) {
    
    }

    void Elevator::Reset() {
        SetPosition(0.0);
        m_currLevel = Level::Zero;
    }

    void Elevator::TaskPeriodic(RobotMode mode) {
        m_position->LogDouble(m_elevatorMotor->GetPosition());
    }
}
