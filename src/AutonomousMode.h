#pragma once

#include "WPILib.h"
#include <iostream>
#include "src/info/RobotInfo.h"
#include "src/auto/AutoRoutine.h"
#include "src/auto/NoAuto.h"
#include "src/auto/ForwardAuto.h"
#include "src/auto/SwitchAuto.h"
#include "src/DisabledMode.h"
#include "src/Robot.h"
#include "src/subsystems/Drive.h"
#include "src/subsystems/Elevator.h"
#include "src/subsystems/Intake.h"
#include "src/subsystems/Claw.h"

using namespace frc;

namespace frc973 {
class AutoRoutine;
class Disabled;

class Autonomous {
public:
    Autonomous(Disabled *disabled, Drive *drive, Elevator *elevator,
               Intake *intake, Claw *claw);
    virtual ~Autonomous();

    void AutonomousInit();
    void AutonomousPeriodic();
    void AutonomousStop();

    static constexpr double DRIVER_STATION_TO_AUTO_LINE =

        private : NoAuto * m_noAuto;
    ForwardAuto *m_forwardAuto;
    SwitchAuto *m_switchAuto;

    Disabled *m_disabled;
};
};
