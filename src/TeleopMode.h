#pragma once

#include <WPILib.h>
#include <iostream>
#include "src/RobotInfo.h"
#include "lib/helpers/JoystickHelper.h"

using namespace frc;

namespace frc973 {
class Teleop {
    public:
        Teleop();
        virtual ~Teleop();

        void TeleopInit();
        void TeleopPeriodic();
        void TeleopStop();

        void HandleTeleopButton(uint32_t port, uint32_t button,
                                bool pressedP);
    };
};
