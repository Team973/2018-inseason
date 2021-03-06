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
#include "lib/helpers/DualActionJoystickHelper.h"
#include "lib/helpers/XboxJoystickHelper.h"
#include "lib/helpers/PoofsJoystickHelper.h"
#include "src/subsystems/Elevator.h"
#include "src/subsystems/Claw.h"
#include "src/subsystems/Wrist.h"
#include "src/subsystems/Hanger.h"
#include "src/subsystems/Drive.h"
#include "src/subsystems/IntakeAssembly.h"
#include "lib/logging/LogSpreadsheet.h"
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

/**
 * Defines the robot.
 */
class Robot
        : public CoopMTRobot
        , public DualActionJoystickObserver
        , public XboxJoystickObserver
        , PoofsJoystickObserver {
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

    void ObservePoofsJoystickStateChange(uint32_t port, uint32_t button,
                                         bool pressedP) override;
    void ObserveDualActionJoystickStateChange(uint32_t port, uint32_t button,
                                              bool pressedP) override;
    void ObserveXboxJoystickStateChange(uint32_t port, uint32_t button,
                                        bool pressedP) override;

    static const int NUM_LED = 26; /**< The number of LEDs. */

private:
    PowerDistributionPanel *m_pdp;

    ObservablePoofsJoystick *m_driverJoystick;
    ObservableXboxJoystick *m_operatorJoystick;

    TalonSRX *m_leftDriveTalonA;
    VictorSPX *m_leftDriveVictorB;
    VictorSPX *m_leftDriveVictorC;
    TalonSRX *m_rightDriveTalonA;
    VictorSPX *m_rightDriveVictorB;
    VictorSPX *m_rightDriveVictorC;

    ADXRS450_Gyro *m_gyro;

    LogSpreadsheet *m_logger;
    LogCell *m_matchIdentifier;
    LogCell *m_gameSpecificMessage;

    UsbCamera m_forkCamera;
    UsbCamera m_intakeCamera;
    CameraServer *m_cameraServer;
    VideoSink m_greyCam;

    Solenoid *m_cubeClamp;
    Solenoid *m_cubeSpring;
    TalonSRX *m_rightRoller;
    TalonSRX *m_leftRoller;
    DigitalInput *m_rightCubeSensor;
    DigitalInput *m_leftCubeSensor;
    TalonSRX *m_elevatorMotor;
    TalonSRX *m_wristMotor;

    Solenoid *m_hangerPTO;
    Solenoid *m_forkDeploy;
    TalonSRX *m_forkliftTalon;
    GreyLight *m_greylight;
    Elevator *m_elevator;
    Claw *m_claw;
    Wrist *m_wrist;
    IntakeAssembly *m_intakeAssembly;
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
