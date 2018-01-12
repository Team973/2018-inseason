/**
 * Contributors:
 * - Kyle
 * - Oliver
 * - Andrew
 **/

#pragma once

#include <WPILib.h>
#include <iostream>
#include "src/info/RobotInfo.h"
#include "src/DisabledMode.h"
#include "src/AutonomousMode.h"
#include "src/TeleopMode.h"
#include "src/TestMode.h"
#include "lib/helpers/JoystickHelper.h"
#include "src/subsystems/Elevator.h"
#include "src/subsystems/Claw.h"
#include "src/subsystems/Hanger.h"
#include "src/subsystems/Drive.h"
#include "lib/logging/LogSpreadsheet.h"
#include "lib/helpers/JoystickHelper.h"
#include "lib/bases/CoopMTRobot.h"

namespace frc973{
class Disabled;
class Autonomous;

class Robot : public CoopMTRobot, public JoystickObserver {
    public:
        Robot();
        virtual ~Robot();

        void Initialize();

        void DisabledStart();
        void DisabledPeriodic();
        void DisabledStop();

        void AutonomousStart();
        void AutonomousPeriodic();
        void AutonomousStop();

        void TeleopStart();
        void TeleopPeriodic();
        void TeleopStop();

        void TestStart();
        void TestPeriodic();
        void TestStop();

        void ObserveJoystickStateChange(uint32_t port, uint32_t button,
                                        bool pressedP) override;
    private:
        PowerDistributionPanel *m_pdp;

        ObservableJoystick *m_driverJoystick;
        ObservableJoystick *m_operatorJoystick;
        ObservableJoystick *m_tuningJoystick;

        Disabled *m_disabled;
        Autonomous *m_autonomous;
        Teleop *m_teleop;
        Test *m_test;

        LogSpreadsheet *m_logger;

        Elevator *m_elevator;
        Claw *m_claw;
        Drive *m_drive;
        Hanger *m_hanger;
    };
};
