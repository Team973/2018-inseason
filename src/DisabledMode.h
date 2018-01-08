#pragma once

#include "WPILib.h"
#include <iostream>
#include "src/RobotInfo.h"
#include "lib/helpers/JoystickHelper.h"
#include "src/Robot.h"
#include "src/AutonomousMode.h"

using namespace frc;

namespace frc973 {
class Disabled {
    public:
        typedef enum routine {
            none,
            forward
        } SelectedAutoRoutine;

        Disabled();
        virtual ~Disabled();

        void DisabledInit();
        void DisabledPeriodic();
        void DisabledStop();

        void HandleDisabledButton(uint32_t port, uint32_t button,
                                  bool pressedP);

        const char *GetRoutineName();
        SelectedAutoRoutine GetRoutine();
    private:
        SelectedAutoRoutine m_routine;
    };
};
