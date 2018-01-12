#include <WPILib.h>
#include <iostream>
#include "src/info/RobotInfo.h"
#include "src/DisabledMode.h"
#include "src/AutonomousMode.h"
#include "src/TeleopMode.h"
#include "src/TestMode.h"
#include "src/Robot.h"

namespace frc973 {
Robot::Robot()
    : m_pdp(new PowerDistributionPanel)
    , m_driverJoystick(new ObservableJoystick(DRIVER_JOYSTICK_PORT, this, this))
    , m_operatorJoystick(new ObservableJoystick(OPERATOR_JOYSTICK_PORT, this, this))
    , m_tuningJoystick(new ObservableJoystick(TUNING_JOYSTICK_PORT, this, this))
    , m_disabled(new Disabled())
    , m_autonomous(new Autonomous(m_disabled))
    , m_teleop(new Teleop())
    , m_test(new Test())
    , m_logger(new LogSpreadsheet(this))
    , m_elevator(new Elevator(this, m_logger))
    , m_claw(new Claw(this, m_logger))
    , m_drive(new Drive(this, m_logger))
    , m_hanger(new Hanger(this, m_logger))
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
}

void Robot::TeleopPeriodic() {
    m_teleop->TeleopPeriodic();
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
                                       bool pressedP){
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
