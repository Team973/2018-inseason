#include "src/subsystems/Drive.h"

using namespace frc;
using namespace ctre;

namespace frc973 {
Drive::Drive(TaskMgr *scheduler, LogSpreadsheet *logger, phoenix::motorcontrol::can::TalonSRX *leftTalonA, phoenix::motorcontrol::can::VictorSPX *leftVictorB, phoenix::motorcontrol::can::VictorSPX *leftVictorC, phoenix::motorcontrol::can::TalonSRX *rightTalonA, phoenix::motorcontrol::can::VictorSPX *rightVictorB, phoenix::motorcontrol::can::VictorSPX *rightVictorC, ADXRS450_Gyro *driveGyro)
             : m_scheduler(scheduler)
             , m_logger(logger)
             , m_leftTalonA(leftTalonA)
             , m_leftVictorB(leftVictorB)
             , m_leftVictorC(leftVictorC)
             , m_rightTalonA(rightTalonA)
             , m_rightVictorB(rightVictorB)
             , m_rightVictorC(rightVictorC)
             , m_driveGyro(driveGyro)
{
    this->m_scheduler->RegisterTask("Drive", this, TASK_PERIODIC);
}

Drive::~Drive() {
    m_scheduler->UnregisterTask(this);
}

void Drive::TaskPeriodic(RobotMode mode) {
}
}
