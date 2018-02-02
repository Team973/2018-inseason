#include "WPILib.h"
#include "networktables/NetworkTableInstance.h"
#include <iostream>
#include "src/info/RobotInfo.h"
#include "src/DisabledMode.h"
#include "src/AutonomousMode.h"
#include "src/TeleopMode.h"
#include "src/TestMode.h"
#include "src/Robot.h"
#include "ctre/Phoenix.h"
#include "lib/helpers/GreyTalon.h"

using namespace frc;
using namespace nt;

namespace frc973 {
Robot::Robot()
        : CoopMTRobot()
        , JoystickObserver()
        , m_driverJoystick(
              new ObservableJoystick(DRIVER_JOYSTICK_PORT, this, this))
        , m_operatorJoystick(
              new ObservableJoystick(OPERATOR_JOYSTICK_PORT, this, this))
        , m_tuningJoystick(
              new ObservableJoystick(TUNING_JOYSTICK_PORT, this, this))
        , m_logger(new LogSpreadsheet(this))
        , m_clawLeftRoller(FactoryReset(new TalonSRX(CLAW_LEFT_ROLLER_CAN_ID)))
        , m_clawRightRoller(
              FactoryReset(new TalonSRX(CLAW_RIGHT_ROLLER_CAN_ID)))
        , m_clawCubeSensor(new DigitalInput(CUBE_BANNER_SENSOR_DIN))
        , m_elevatorMotor(FactoryReset(new TalonSRX(ELEVATOR_CAN_ID)))
        , m_elevator(
              new Elevator(this, m_logger, m_driverJoystick, m_elevatorMotor))
        , m_claw(new Claw(this, m_logger, m_clawLeftRoller, m_clawRightRoller,
                          m_clawCubeSensor))
        , m_drive(new Drive(this, m_logger))
        , m_hanger(new Hanger(this, m_logger))
        , m_disabled(new Disabled(m_driverJoystick, m_operatorJoystick,
                                  m_tuningJoystick))
        , m_autonomous(new Autonomous(m_disabled))
        , m_teleop(new Teleop(m_driverJoystick, m_operatorJoystick,
                              m_tuningJoystick))
        , m_test(new Test(m_driverJoystick, m_operatorJoystick,
                          m_tuningJoystick, m_elevator))
        , m_dashboard(NetworkTableInstance::GetDefault()) {
    std::cout << "Constructed a Robot!" << std::endl;
}

Robot::~Robot() {
}

void Robot::Initialize() {
}

void Robot::DisabledStart() {
    m_disabled->DisabledInit();
}

void Robot::DisabledContinuous() {
    m_disabled->DisabledPeriodic();
}

void Robot::DisabledStop() {
    m_disabled->DisabledStop();
}

void Robot::AutonomousStart() {
    m_autonomous->AutonomousInit();
}

void Robot::AutonomousContinuous() {
    m_autonomous->AutonomousPeriodic();
}

void Robot::AutonomousStop() {
    m_autonomous->AutonomousStop();
}

void Robot::TeleopStart() {
    m_teleop->TeleopInit();
}

void Robot::TeleopContinuous() {
    m_teleop->TeleopPeriodic();
}

void Robot::TeleopStop() {
    m_teleop->TeleopStop();
}

void Robot::TestStart() {
    m_test->TestInit();
}

void Robot::TestContinuous() {
    m_test->TestPeriodic();
}

void Robot::TestStop() {
    m_test->TestStop();
}

void Robot::RobotPeriodic() {
}

void Robot::ObserveJoystickStateChange(uint32_t port, uint32_t button,
                                       bool pressedP) {
    printf("Button Pressed\n");
    if (this->IsOperatorControl()) {
        m_teleop->HandleTeleopButton(port, button, pressedP);
    }
    else if (this->IsDisabled()) {
        m_disabled->HandleDisabledButton(port, button, pressedP);
    }
    else if (this->IsTest()) {
        m_test->HandleTestButton(port, button, pressedP);
    }
}
}

START_ROBOT_CLASS(frc973::Robot);
