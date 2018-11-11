#pragma once

#include "WPILib.h"
#include <iostream>
#include "src/info/RobotInfo.h"
#include "src/auto/AutoRoutineBase.h"
#include "src/auto/NoAuto.h"
#include "src/auto/ForwardAuto.h"
#include "src/auto/CenterSwitchAuto.h"
#include "src/auto/ScaleAuto.h"
#include "src/auto/SneakScale.h"
#include "src/auto/SwitchOpposite.h"
#include "src/auto/ScaleOpposite.h"
#include "src/auto/SideSwitch.h"
#include "lib/util/WrapDash.h"
#include "src/DisabledMode.h"
#include "src/Robot.h"
#include "src/subsystems/Drive.h"
#include "src/subsystems/IntakeAssembly.h"
#include "lib/helpers/GreyLight.h"
#include "lib/pixelprocessors/AutoIndicator.h"

using namespace frc;

namespace frc973 {
class Disabled;

class Autonomous {
public:
    enum class SwitchScalePosition
    {
        LL,
        LR,
        RR,
        RL,
        NOT_YET_RECEIVED
    };

    Autonomous(Disabled *disabled, Drive *drive, IntakeAssembly *intakeAssembly,
               ADXRS450_Gyro *gyro, GreyLight *greylight);
    virtual ~Autonomous();

    void AutonomousInit();
    void AutonomousPeriodic();
    void AutonomousStop();

    SwitchScalePosition GetSwitchScalePosition(std::string message);

private:
    NoAuto *m_noAuto;
    ForwardAuto *m_forwardAuto;
    CenterSwitchAuto *m_centerSwitchAuto;
    ScaleAuto *m_scaleAuto;
    SneakScale *m_sneakScale;
    ScaleOpposite *m_scaleOpposite;
    SideSwitch *m_sideSwitch;
    SwitchOpposite *m_switchOpposite;

    Disabled *m_disabled;
    GreyLight *m_greylight;
    LightPattern::AutoIndicator *m_autoSignal;

    std::string m_scoringLocations;
    Autonomous::SwitchScalePosition m_switchScalePosition;
    AutoRoutineBase *m_routine;
    AutoRoutineBase::AutoDirection m_direction;
    std::string m_scalePos;

    Drive *m_drive;
    IntakeAssembly *m_intakeAssembly;
    ADXRS450_Gyro *m_gyro;
};
};
