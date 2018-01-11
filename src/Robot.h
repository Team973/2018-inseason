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

namespace frc973{
class Disabled;
class Autonomous;

class Robot : public IterativeRobot, public JoystickObserver {
    public:
        Robot();
        virtual ~Robot();

        void DisabledInit();
        void DisabledPeriodic();
        void DisabledStop();

        void AutonomousInit();
        void AutonomousPeriodic();
        void AutonomousStop();

        void TeleopInit();
        void TeleopPeriodic();
        void TeleopStop();

        void TestInit();
        void TestPeriodic();
        void TestStop();

        void ObserveJoystickStateChange(uint32_t port, uint32_t button,
                                        bool pressedP) override;
    private:
        Disabled *m_disabled;
        Autonomous *m_autonomous;
        Teleop *m_teleop;
        Test *m_test;
    };
};
