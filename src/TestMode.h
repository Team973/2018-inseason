#pragma once

#include <WPILib.h>
#include <iostream>
#include "src/info/RobotInfo.h"
#include "lib/helpers/JoystickHelper.h"

using namespace frc;

namespace frc973 {
class Test {
    public:
        Test();
        virtual ~Test();

        void TestInit();
        void TestPeriodic();
        void TestStop();

        void HandleTestButton(uint32_t port, uint32_t button,
                              bool pressedP);
    };
};
