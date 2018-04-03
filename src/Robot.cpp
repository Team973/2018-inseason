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
#include "lib/util/WrapDash.h"

using namespace frc;
using namespace ctre;
namespace frc973 {
Robot::Robot()
        : CoopMTRobot()
        , JoystickObserver()
        , m_pdp(new PowerDistributionPanel())
        , m_driverJoystick(
              new ObservableJoystick(DRIVER_JOYSTICK_PORT, this, this))
        , m_operatorJoystick(
              new ObservableJoystick(OPERATOR_JOYSTICK_PORT, this, this))
        , m_leftDriveTalonA(new GreyTalonSRX(LEFT_DRIVE_A_CAN_ID))
        , m_leftDriveVictorB(new VictorSPX(LEFT_DRIVE_B_VICTOR_ID))
        , m_leftDriveVictorC(new VictorSPX(LEFT_DRIVE_C_VICTOR_ID))
        , m_rightDriveTalonA(new GreyTalonSRX(RIGHT_DRIVE_A_CAN_ID))
        , m_rightDriveVictorB(new VictorSPX(RIGHT_DRIVE_B_VICTOR_ID))
        , m_rightDriveVictorC(new VictorSPX(RIGHT_DRIVE_C_VICTOR_ID))
        , m_gyro(new ADXRS450_Gyro())
        , m_logger(new LogSpreadsheet(this))
        , m_matchIdentifier(new LogCell("Match Identifier", 64))
        , m_gameSpecificMessage(new LogCell("GameSpecificMessage", 10))
        , m_forkCamera(UsbCamera("USB Camera 0", 0))
        , m_intakeCamera(UsbCamera("USB Camera 1", 1))
        , m_cameraServer(CameraServer::GetInstance())
        , m_greyCam(m_cameraServer->AddServer("serve_GreyCam", 1181))
        , m_cubeClamp(new Solenoid(PCM_CAN_ID, CUBE_CLAMP_PCM_ID))
        , m_rightRoller(new GreyTalonSRX(CLAW_RIGHT_ROLLER_CAN_ID))
        , m_leftRoller(new GreyTalonSRX(CLAW_LEFT_ROLLER_CAN_ID))
        , m_rightCubeSensor(
              new DigitalInput(RIGHT_INTAKE_BEAM_BREAKER_SENSOR_DIN))
        , m_leftCubeSensor(
              new DigitalInput(LEFT_INTAKE_BEAM_BREAKER_SENSOR_DIN))
        , m_elevatorMotor(new GreyTalonSRX(ELEVATOR_CAN_ID))
        , m_wristMotor(new GreyTalonSRX(WRIST_CAN_ID))
        , m_hangerPTO(new Solenoid(PCM_CAN_ID, HANGER_PTO_PCM_ID))
        , m_forkDeploy(new Solenoid(PCM_CAN_ID, FORK_DEPLOY_PCM_ID))
        , m_forkliftTalon(new GreyTalonSRX(FORKLIFT_TALON_CAN_ID))
        , m_greylight(new GreyLight(NUM_LED))
        , m_elevator(new Elevator(this, m_logger, m_elevatorMotor))
        , m_intake(new Intake(this, m_logger, m_rightCubeSensor,
                              m_leftCubeSensor, m_leftRoller, m_rightRoller,
                              m_cubeClamp))
        , m_wrist(new Wrist(this, m_logger, m_wristMotor))
        , m_intakeAssembly(new IntakeAssembly(this, m_logger,
                                              m_operatorJoystick, m_elevator,
                                              m_intake, m_wrist, m_greylight))
        , m_drive(new Drive(this, m_logger, m_leftDriveTalonA,
                            m_leftDriveVictorB, m_leftDriveVictorC,
                            m_rightDriveTalonA, m_rightDriveVictorB,
                            m_rightDriveVictorC, m_gyro))
        , m_hanger(new Hanger(this, m_logger, m_drive, m_elevator, m_hangerPTO,
                              m_forkDeploy, m_forkliftTalon, m_intakeCamera,
                              m_forkCamera, m_greyCam, m_greylight))
        , m_airPressureSwitch(new DigitalInput(PRESSURE_DIN_ID))
        , m_compressorRelay(
              new Relay(COMPRESSOR_RELAY, Relay::Direction::kForwardOnly))
        , m_compressor(
              new GreyCompressor(m_airPressureSwitch, m_compressorRelay, this))
        , m_disabled(new Disabled(m_driverJoystick, m_operatorJoystick,
                                  m_intakeAssembly, m_intakeCamera,
                                  m_forkCamera, m_greyCam, m_greylight))
        , m_autonomous(new Autonomous(m_disabled, m_drive, m_intakeAssembly,
                                      m_gyro, m_greylight))
        , m_teleop(new Teleop(m_driverJoystick, m_operatorJoystick, m_drive,
                              m_intakeAssembly, m_hanger, m_greylight))
        , m_test(new Test(m_driverJoystick, m_operatorJoystick, m_drive,
                          m_intakeAssembly, m_hanger, m_greylight)) {
    std::cout << "Constructed a Robot!" << std::endl;
}

Robot::~Robot() {
}

void Robot::Initialize() {
    m_compressor->Enable();
    m_logger->RegisterCell(m_matchIdentifier);
    m_logger->RegisterCell(m_gameSpecificMessage);
    m_logger->Start();
    m_cameraServer->AddCamera(m_intakeCamera);
    m_cameraServer->AddCamera(m_forkCamera);
    m_intakeCamera.SetVideoMode(VideoMode::PixelFormat::kMJPEG, 160, 120, 10);
    m_forkCamera.SetVideoMode(VideoMode::PixelFormat::kMJPEG, 160, 120, 10);
    m_greyCam.SetSource(m_intakeCamera);
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

void Robot::AllStateContinuous() {
    // NetworkTable Battery Voltage
    SmartDashboard::PutNumber("misc/pdp/batteryvoltage", m_pdp->GetVoltage());

    m_matchIdentifier->LogPrintf(
        "%s_%s%dm%d", DriverStation::GetInstance().GetEventName().c_str(),
        MatchTypeToString(DriverStation::GetInstance().GetMatchType()),
        DriverStation::GetInstance().GetMatchNumber(),
        DriverStation::GetInstance().GetReplayNumber());
    m_gameSpecificMessage->LogText(
        DriverStation::GetInstance().GetGameSpecificMessage().c_str());
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
