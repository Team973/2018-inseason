#include <WPILib.h>
#include <iostream>
#include "src/RobotInfo.h"
#include "src/DisabledMode.h"
#include "src/AutonomousMode.h"
#include "src/TeleopMode.h"
#include "src/TestMode.h"
#include "src/Robot.h"

namespace frc973 {
Robot::Robot()
    : m_disabled(new Disabled())
    , m_autonomous(new Autonomous(m_disabled))
    , m_teleop(new Teleop())
    , m_test(new Test())
{
    std::cout << "Constructed a Robot!" << std::endl;
}

Robot::~Robot(){
}

void Robot::DisabledInit() {
    m_disabled->DisabledInit();
}

void Robot::DisabledPeriodic() {
    m_disabled->DisabledPeriodic();
}

void Robot::DisabledStop() {
    m_disabled->DisabledStop();
}

void Robot::AutonomousInit() {
    m_autonomous->AutonomousInit();
}

void Robot::AutonomousPeriodic() {
    m_autonomous->AutonomousPeriodic();
}

void Robot::AutonomousStop() {
    m_autonomous->AutonomousStop();
}

void Robot::TeleopInit() {
    m_teleop->TeleopInit();
}

void Robot::TeleopPeriodic() {
    m_teleop->TeleopPeriodic();
}

void Robot::TeleopStop() {
    m_teleop->TeleopStop();
}

void Robot::TestInit() {
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
