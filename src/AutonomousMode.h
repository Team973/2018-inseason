#pragma once

#include <WPILib.h>
#include <iostream>
#include "src/info/RobotInfo.h"
#include "src/auto/AutoRoutine.h"
#include "src/auto/NoAuto.h"
#include "src/auto/ForwardAuto.h"
#include "src/DisabledMode.h"
#include "src/Robot.h"

using namespace frc;

namespace frc973 {
class AutoRoutine;
class Disabled;

class Autonomous {
    public:
        Autonomous(Disabled *disabled);
        virtual ~Autonomous();

        void AutonomousInit();
        void AutonomousPeriodic();
        void AutonomousStop();
    private:
        NoAuto *m_noAuto;
        ForwardAuto *m_forwardAuto;

        Disabled *m_disabled;
    };
};
