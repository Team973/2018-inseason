#pragma once

#include "WPILib.h"
#include <iostream>
#include "src/info/RobotInfo.h"
#include "src/auto/AutoRoutine.h"
#include "src/auto/NoAuto.h"
#include "src/auto/ForwardAuto.h"
#include "src/auto/SwitchAuto.h"
#include "src/auto/ScaleAuto.h"
#include "src/DisabledMode.h"
#include "src/Robot.h"
#include "lib/util/WrapDash.h"

using namespace frc;

namespace frc973 {
class Disabled;
class Autonomous {
public:
    enum SwitchScalePosition { LL, LR, RR, RL};

    enum SelectedAutoRoutine { noAuto, forward, lowGoal, highGoal};

    Autonomous(Disabled *disabled);
    virtual ~Autonomous();

    void AutonomousInit();
    void AutonomousPeriodic();
    void AutonomousStop();

    SwitchScalePosition GetSwitchScalePosition(std::string message);
    const char *GetRoutineName();

private:
    NoAuto *m_noAuto;
    ForwardAuto *m_forwardAuto;
    SwitchAuto *m_switchAuto;
    ScaleAuto *m_scaleAuto;

    Disabled *m_disabled;

    std::string m_scoringLocations;
    SwitchScalePosition m_switchScalePosition;
    SelectedAutoRoutine m_routine;
};
};
