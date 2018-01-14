#include <stdio.h>
#include "WPILib.h"
#include "src/controllers/ArcadeDriveController.h"
#include "src/controllers/OpenloopArcadeDriveController.h"
#include "src/controllers/AssistedArcadeDrive.h"
#include "src/controllers/PIDDrive.h"
#include "src/controllers/StraightDriveController.h"
#include "src/controllers/SplineDriveController.h"
#include "src/controllers/TrapDriveController.h"
#include "src/info/RobotInfo.h"
#include "src/subsystems/Drive.h"
#include "lib/util/Util.h"
#include "lib/util/WrapDash.h"
#include "lib/logging/LogSpreadsheet.h"

using namespace frc;
using namespace ctre;

namespace frc973 {
Drive::Drive(TaskMgr *scheduler, LogSpreadsheet *logger, TalonSRX *leftDriveTalonA, VictorSPX *leftDriveVictorB, VictorSPX *leftDriveVictorC, TalonSRX *rightDriveTalonA, VictorSPX *rightDriveVictorB, VictorSPX *rightDriveVictorC, ADXRS450_Gyro *gyro)
             : DriveBase(scheduler, this, this, nullptr)
             , m_logger(logger)
             , m_leftDriveTalonA(leftDriveTalonA)
             , m_leftDriveVictorB(leftDriveVictorB)
             , m_leftDriveVictorC(leftDriveVictorC)
             , m_rightDriveTalonA(rightDriveTalonA)
             , m_rightDriveVictorB(rightDriveVictorB)
             , m_rightDriveVictorC(rightDriveVictorC)
             , m_controlMode(phoenix::motorcontrol::ControlMode::PercentOutput)
             , m_leftDriveOutput(0.0)
             , m_rightDriveOutput(0.0)
             , m_leftDriveOutputLog(new LogCell("Left motor signal (pow or vel)"))
             , m_rightDriveOutputLog(new LogCell("Right motor signal (pow or vel)"))
             , m_leftVoltageLog(new LogCell("Left motor voltage"))
             , m_rightVoltageLog(new LogCell("Right motor voltage"))
             , m_leftPosZero(0.0)
             , m_rightPosZero(0.0)
             , m_gyro(gyro)
             , m_gyroZero(0.0)
             , m_arcadeDriveController(new ArcadeDriveController())
             , m_openloopArcadeDriveController(new OpenloopArcadeDriveController())
             , m_assistedArcadeDriveController(new AssistedArcadeDriveController())
             , m_pidDriveController(new PIDDriveController())
             , m_trapDriveController(new TrapDriveController(this, logger))
             , m_straightDriveController(new StraightDriveController())
             , m_splineDriveController(new SplineDriveController(this, logger))
             , m_angle()
             , m_angleRate()
             , m_angleLog(new LogCell("Angle"))
             , m_angularRateLog(new LogCell("Angular Rate"))
             , m_leftDistLog(new LogCell("Left Encoder Distance"))
             , m_leftDistRateLog(new LogCell("Left Encoder Rate"))
             , m_rightDistLog(new LogCell("Right Encoder Distance"))
             , m_rightDistRateLog(new LogCell("Right Encoder Rate"))
             , m_currentLog(new LogCell("Drive current"))
{
    this->SetDriveController(m_arcadeDriveController);
    this->SetDriveControlMode(m_controlMode);

    m_leftDriveTalonA->SetNeutralMode(Coast);

    m_leftDriveVictorB->Follow(*m_leftDriveTalonA);

    m_leftDriveVictorC->Follow(*m_leftDriveTalonA);

    m_rightDriveTalonA->SetNeutralMode(Coast);

    m_rightDriveVictorB->Follow(*m_rightDriveTalonA);

    m_rightDriveVictorC->Follow(*m_rightDriveTalonA);
}

Drive::~Drive() {};


/**
 * Sets Drive controller to ArcadeDrive
 *
 * @param throttle  Left joystick y-axis value
 * @param turn      Right joystick x-axis value
 */
void Drive::ArcadeDrive(double throttle, double turn) {
    this->SetDriveController(m_arcadeDriveController);
    m_arcadeDriveController->SetJoysticks(throttle, turn);
}

/**
 * Sets Drive controller to OpenLoopArcadeDrive
 *
 * @param throttle  Left joystick y-axis value
 * @param turn      Right joystick x-axis value
 */
void Drive::OpenloopArcadeDrive(double throttle, double turn) {
    this->SetDriveController(m_openloopArcadeDriveController);
    m_openloopArcadeDriveController->SetJoysticks(throttle, turn);
}

/**
 * Sets Drive controller to AssistedArcadeDrive
 *
 * @param throttle  Left joystick y-axis value
 * @param turn      Right joystick x-axis value
 */
void Drive::AssistedArcadeDrive(double throttle, double turn) {
    this->SetDriveController(m_assistedArcadeDriveController);
    m_assistedArcadeDriveController->SetJoysticks(throttle, turn);
}

/**
 * Sets Drive mode to PIDDrive
 *
 * @param dist        Desired drive distance
 * @param turn        Desired turn angle
 * @param relativity  Calculates relativity of drive distance and current position
 * @param powerCap    Percentage of drive power; 1.0 = full power
 *
 * @return            the PID Drive contoller
 */
PIDDriveController *Drive::PIDDrive(double dist, double turn,
        RelativeTo relativity, double powerCap)
{
    this->SetDriveController(m_pidDriveController);
    m_pidDriveController->SetCap(powerCap);
    m_pidDriveController->SetTarget(dist, turn,
            relativity, this);
    m_pidDriveController->EnableDist();
    return m_pidDriveController;
}

/**
 * Sets Drive mode to PIDTurn
 *
 * @param turn        Desired turn angle
 * @param relativity  Calculates relativity of drive distance and current position
 * @param powerCap    Percentage of drive power; 1.0 = full power
 *
 * @return            the PID Drive contoller
 */
PIDDriveController *Drive::PIDTurn(double turn, RelativeTo relativity,
        double powerCap)
{
    this->SetDriveController(m_pidDriveController);
    m_pidDriveController->SetCap(powerCap);
    m_pidDriveController->SetTarget(0.0, turn,
            relativity, this);
    m_pidDriveController->DisableDist();
    return m_pidDriveController;
}

/**
 * Returns Left Drive Distance thorugh encoder translation
 *
 * @return  Left Drive Distance reported in inches
 */
double Drive::GetLeftDist() const {
    return m_leftDriveTalonA->GetSelectedSensorPosition(0) * DRIVE_DIST_PER_REVOLUTION -
        m_leftPosZero;
}

/**
 * Returns Right Drive Distance thorugh encoder translation
 *
 * @return  Right Drive Distance reported in inches
 */
double Drive::GetRightDist() const {
    return -m_rightDriveTalonA->GetSelectedSensorPosition(0) * DRIVE_DIST_PER_REVOLUTION -
        m_rightPosZero;
}

/**
 * Returns Left Drive Rate or speed thorugh encoder translation
 *
 * @return  Left Drive Rate or Speed reported in inches Reported in inches per second; As per manual 17.2.1, GetSpeed reports RPM
 */
double Drive::GetLeftRate() const {
    return m_leftDriveTalonA->GetSelectedSensorVelocity(0) * DRIVE_IPS_FROM_RPM;
}

/**
 * Returns Right Drive Rate or speed thorugh encoder translation
 *
 * @return  Right Drive Rate or Speed reported in inches Reported in inches per second; As per manual 17.2.1, GetSpeed reports RPM
 */
double Drive::GetRightRate() const {
    return -m_rightDriveTalonA->GetSelectedSensorVelocity(0) * DRIVE_IPS_FROM_RPM;
}

/**
 * Returns Average Drive Distance thorugh encoder translation
 *
 * @return  Average Drive Distance reported in inches
 */
double Drive::GetDist() const {
    return (GetLeftDist() + GetRightDist()) / 2.0;
}

/**
 * Returns Average Drive Rate or speed thorugh encoder translation
 *
 * @return  Average Drive Rate or Speed reported in inches Reported in inches per second; As per manual 17.2.1, GetSpeed reports RPM
 */
double Drive::GetRate() const {
    return (GetLeftRate() + GetRightRate()) / 2.0;
}

/**
 * Returns Average Drive Current thorugh Talon SRX Output
 *
 * @return  Avergage current reported in amperes
 */
double Drive::GetDriveCurrent() const {
    return (Util::abs(m_rightDriveTalonA->GetOutputCurrent()) +
            Util::abs(m_leftDriveTalonA->GetOutputCurrent())) / 2.0;
}

/**
 * Returns calculated current angle thorugh gyro translation
 *
 * @return  Current angle position with respect to initial position
 */
double Drive::GetAngle() const {
    return -(m_angle - m_gyroZero);
}

/**
 * Returns calculated current anglular rate thorugh gyro translation
 *
 * @return  Current angular rate
 */
double Drive::GetAngularRate() const {
    return -m_angleRate;
}

/**
 * Calculates Drive Output and sets it from driver input or closed control loop
 *
 * @param left  desired left Output
 * @param right desired right Output
 */
void Drive::SetDriveOutput(double left, double right) {
    m_leftDriveOutput = left;
    m_rightDriveOutput = right;

    if (m_controlMode == phoenix::motorcontrol::ControlMode::Velocity) {
        m_leftDriveOutput /= DRIVE_IPS_FROM_RPM;
        m_rightDriveOutput /= DRIVE_IPS_FROM_RPM;
    }
    else if (m_controlMode == phoenix::motorcontrol::ControlMode::Position) {
        m_leftDriveOutput /= DRIVE_DIST_PER_REVOLUTION;
        m_rightDriveOutput /= DRIVE_DIST_PER_REVOLUTION;
    }

    if (std::isnan(m_leftDriveOutput) || std::isnan(m_rightDriveOutput)) {
        m_leftDriveTalonA->Set(m_controlMode, 0.0);
        m_rightDriveTalonA->Set(m_controlMode, 0.0);
    }
    else {
        m_leftDriveTalonA->Set(m_controlMode, m_leftDriveOutput);
        m_rightDriveTalonA->Set(m_controlMode, -m_rightDriveOutput);
    }
}

/**
 * Set Drive Talon control modes
 */
void Drive::SetDriveControlMode(phoenix::motorcontrol::ControlMode mode) {
    m_controlMode = mode;
}

void Drive::TaskPeriodic(RobotMode mode) {
    m_angle = m_gyro->GetAngle();

    //Austin ADXRS450_Gyro config
    double currRate = m_gyro->GetRate();
    if(currRate == 0){
    }
    else{
      m_angleRate = currRate;
    }

    DBStringPrintf(DB_LINE9, "l %2.1lf r %2.1lf g %2.1lf",
            this->GetLeftDist(),
            this->GetRightDist(),
            this->GetAngle());

    m_angleLog->LogDouble(GetAngle());
    m_angularRateLog->LogDouble(GetAngularRate());

    m_leftDistLog->LogDouble(GetLeftDist());
    m_leftDistRateLog->LogDouble(GetLeftRate());

    m_rightDistLog->LogDouble(GetRightDist());
    m_rightDistRateLog->LogDouble(GetRightRate());

    if (m_controlMode == phoenix::motorcontrol::ControlMode::Velocity) {
        m_leftDriveOutputLog->LogDouble(m_leftDriveOutput * DRIVE_IPS_FROM_RPM);
        m_rightDriveOutputLog->LogDouble(m_rightDriveOutput * DRIVE_IPS_FROM_RPM);
    }
    else if (m_controlMode == phoenix::motorcontrol::ControlMode::Position) {
        m_leftDriveOutputLog->LogDouble(m_leftDriveOutput * DRIVE_DIST_PER_REVOLUTION);
        m_rightDriveOutputLog->LogDouble(m_rightDriveOutput * DRIVE_DIST_PER_REVOLUTION);
    }
    else {
        m_leftDriveOutputLog->LogDouble(m_leftDriveOutput);
        m_rightDriveOutputLog->LogDouble(m_rightDriveOutput);
    }

    m_leftVoltageLog->LogDouble(m_leftDriveTalonA->GetMotorOutputVoltage());
    m_rightVoltageLog->LogDouble(m_rightDriveTalonA->GetMotorOutputVoltage());

    m_currentLog->LogDouble(GetDriveCurrent());
}

void Drive::DriveStraight(RelativeTo relativity, double dist, double angle) {
    this->SetDriveController(m_straightDriveController);
    m_straightDriveController->SetTarget(relativity, dist, angle, this);
}

TrapDriveController *Drive::TrapDrive(RelativeTo relativity,
        double dist, double angle) {
    this->SetDriveController(m_trapDriveController);
    m_trapDriveController->SetTarget(relativity, dist, angle);
    return m_trapDriveController;
}

SplineDriveController *Drive::SplineDrive(RelativeTo relativity,
        double dist, double angle) {
    this->SetDriveController(m_splineDriveController);
    m_splineDriveController->SetTarget(relativity, dist, angle);
    return m_splineDriveController;
}
}
