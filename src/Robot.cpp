#include "WPILib.h"
#include "Phoenix.h"
#include <iostream>
#include "src/info/RobotInfo.h"
#include "src/DisabledMode.h"
#include "src/AutonomousMode.h"
#include "src/TeleopMode.h"
#include "src/TestMode.h"
#include "src/Robot.h"
#include "ctre/Phoenix.h"

using namespace frc;
using namespace ctre;

namespace frc973 {
Robot::Robot()
    : m_driverJoystick(new ObservableJoystick(DRIVER_JOYSTICK_PORT, this, this))
    , m_operatorJoystick(new ObservableJoystick(OPERATOR_JOYSTICK_PORT, this, this))
    , m_tuningJoystick(new ObservableJoystick(TUNING_JOYSTICK_PORT, this, this))
    , m_leftDriveTalonA(new TalonSRX(LEFT_DRIVE_A_CAN_ID))
    , m_leftDriveVictorB(new VictorSPX(LEFT_DRIVE_B_VICTOR_ID))
    , m_leftDriveVictorC(new VictorSPX(LEFT_DRIVE_C_VICTOR_ID))
    , m_rightDriveTalonA(new TalonSRX(RIGHT_DRIVE_A_CAN_ID))
    , m_rightDriveVictorB(new VictorSPX(RIGHT_DRIVE_B_VICTOR_ID))
    , m_rightDriveVictorC(new VictorSPX(RIGHT_DRIVE_C_VICTOR_ID))
    , m_gyro(new ADXRS450_Gyro())
    , m_logger(new LogSpreadsheet(this))
    , m_elevator(new Elevator(this, m_logger, m_driverJoystick))
    , m_claw(new Claw(this, m_logger))
    , m_drive(new Drive(this, m_logger, m_leftDriveTalonA, m_leftDriveVictorB, m_leftDriveVictorC, m_rightDriveTalonA, m_rightDriveVictorB, m_rightDriveVictorC, m_gyro))
    , m_hanger(new Hanger(this, m_logger))
    , m_disabled(new Disabled(m_driverJoystick, m_operatorJoystick, m_tuningJoystick))
    , m_autonomous(new Autonomous(m_disabled))
    , m_teleop(new Teleop(m_driverJoystick, m_operatorJoystick, m_tuningJoystick))
    , m_test(new Test(m_driverJoystick, m_operatorJoystick, m_tuningJoystick, m_elevator))
{
    std::cout << "Constructed a Robot!" << std::endl;
}

Robot::~Robot(){
}

void Robot::Initialize() {
}

void Robot::DisabledStart() {
    m_disabled->DisabledInit();
}

void Robot::DisabledPeriodic() {
    m_disabled->DisabledPeriodic();
}

void Robot::DisabledStop() {
    m_disabled->DisabledStop();
}

void Robot::AutonomousStart() {
    m_autonomous->AutonomousInit();
}

void Robot::AutonomousPeriodic() {
    m_autonomous->AutonomousPeriodic();
}

void Robot::AutonomousStop() {
    m_autonomous->AutonomousStop();
}

void Robot::TeleopStart() {
    m_teleop->TeleopInit();
    m_drive->ArcadeDrive(0.0, 0.0);
}

void Robot::TeleopPeriodic() {
    m_teleop->TeleopPeriodic();
    double y = -m_driverJoystick->GetRawAxisWithDeadband(DualAction::LeftYAxis);
    double x = -m_driverJoystick->GetRawAxisWithDeadband(DualAction::RightXAxis) + -m_tuningJoystick->GetRawAxisWithDeadband(DualAction::RightXAxis);
    static bool g_manualDriveControl = true;

    if(g_manualDriveControl) {
        if(m_driverJoystick->GetRawButton(DualAction::RightBumper)) {
            x /= 3.0;
            y /= 3.0;
        }

        if(m_driveMode == DriveMode::OpenLoop){
            m_drive->OpenloopArcadeDrive(y, x);
        }
        else if(m_driveMode == DriveMode::AssistedArcade){
            m_drive->AssistedArcadeDrive(y, x);
        }
    }

    if (m_driverJoystick->GetRawButton(2)) {
        m_elevator->SetPower(0.25);
    }
}

void Robot::TeleopStop() {
    m_teleop->TeleopStop();
}

void Robot::TestStart() {
    m_test->TestInit();
}

void Robot::TestPeriodic(){
    m_test->TestPeriodic();
}

void Robot::TestStop() {
    m_test->TestStop();
}

void Robot::ObserveJoystickStateChange(uint32_t port, uint32_t button,
                                       bool pressedP) {
    if (this->IsOperatorControl()){
        m_teleop->HandleTeleopButton(port, button, pressedP);
    }
    else if (this->IsDisabled()){
        m_disabled->HandleDisabledButton(port, button, pressedP);
    }
    else if (this->IsTest()){
        m_test->HandleTestButton(port, button, pressedP);
    }
}
}

START_ROBOT_CLASS(frc973::Robot);
