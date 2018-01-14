#include "src/subsystems/Drive.h"

using namespace frc;
using namespace ctre;

namespace frc973 {
Drive::Drive(TaskMgr *scheduler, LogSpreadsheet *logger, TalonSRX *leftDriveTalonA, VictorSPX *leftDriveVictorB, VictorSPX *leftDriveVictorC, TalonSRX *rightDriveTalonA, VictorSPX *rightDriveVictorB, VictorSPX *rightDriveVictorC, ADXRS450_Gyro *driveGyro)
             : m_scheduler(scheduler)
             , m_logger(logger)
             , m_leftDriveTalonA(leftDriveTalonA)
             , m_leftDriveVictorB(leftDriveVictorB)
             , m_leftDriveVictorC(leftDriveVictorC)
             , m_rightDriveTalonA(rightDriveTalonA)
             , m_rightDriveVictorB(rightDriveVictorB)
             , m_rightDriveVictorC(rightDriveVictorC)
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
