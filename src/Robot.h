/**
 * Contributors:
 * - Natalie
 * - Kyle
 * - Oliver
 * - Andrew
 * - Allen
 * - Chris L
 * - Garrett R
 * - Cole B
 **/

#pragma once

#include "WPILib.h"
#include "Phoenix.h"
#include <iostream>
#include "src/info/RobotInfo.h"
#include "src/DisabledMode.h"
#include "src/AutonomousMode.h"
#include "src/TeleopMode.h"
#include "src/TestMode.h"
#include "lib/helpers/JoystickHelper.h"
#include "src/subsystems/Elevator.h"
#include "src/subsystems/Claw.h"
#include "src/subsystems/Intake.h"
#include "src/subsystems/Hanger.h"
#include "src/subsystems/Drive.h"
#include "lib/logging/LogSpreadsheet.h"
#include "lib/helpers/JoystickHelper.h"
#include "lib/helpers/GreyCompressor.h"
#include "lib/helpers/GreyTalon.h"
#include "lib/bases/CoopMTRobot.h"
#include "ctre/Phoenix.h"
#include "lib/helpers/GreyTalon.h"
#include "lib/helpers/GreyLight.h"

using namespace frc;
using namespace ctre;
using namespace cs;

namespace frc973 {
class Disabled;
class Autonomous;
class Drive;

class Robot
        : public CoopMTRobot
        , public JoystickObserver {
public:
    Robot();
    virtual ~Robot();

    void Initialize() override;

    void DisabledStart() override;
    void DisabledContinuous() override;
    void DisabledStop() override;

    void AutonomousStart() override;
    void AutonomousContinuous() override;
    void AutonomousStop() override;

    void TeleopStart() override;
    void TeleopContinuous() override;
    void TeleopStop() override;

    void TestStart() override;
    void TestContinuous() override;
    void TestStop() override;

    void AllStateContinuous() override;

    void ObserveJoystickStateChange(uint32_t port, uint32_t button,
                                    bool pressedP) override;

private:
    PowerDistributionPanel *m_pdp;

    ObservableJoystick *m_driverJoystick;
    ObservableJoystick *m_operatorJoystick;

    TalonSRX *m_leftDriveTalonA;
    VictorSPX *m_leftDriveVictorB;
    VictorSPX *m_leftDriveVictorC;
    TalonSRX *m_rightDriveTalonA;
    VictorSPX *m_rightDriveVictorB;
    VictorSPX *m_rightDriveVictorC;

    ADXRS450_Gyro *m_gyro;

    LogSpreadsheet *m_logger;

    UsbCamera m_forkCamera;
    UsbCamera m_intakeCamera;
    CameraServer *m_cameraServer;
    VideoSink m_greyCam;

    Solenoid *m_cubeClamp;
    Solenoid *m_clawKicker;
    Solenoid *m_intakePosition;
    Solenoid *m_intakeOpenClose;
    TalonSRX *m_rightRoller;
    TalonSRX *m_leftRoller;
    DigitalInput *m_cubeSensor;
    TalonSRX *m_elevatorMotor;
    Solenoid *m_hangerPTO;
    TalonSRX *m_forkliftTalon;
    GreyLight *m_greylight;
    Elevator *m_elevator;
    Claw *m_claw;
    Intake *m_intake;
    Drive *m_drive;
    Hanger *m_hanger;

    DigitalInput *m_airPressureSwitch;
    Relay *m_compressorRelay;
    GreyCompressor *m_compressor;
    Disabled *m_disabled;
    Autonomous *m_autonomous;
    Teleop *m_teleop;
    Test *m_test;
};
};
