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

/**
 * Controls the autonomous mode.
 */
class Autonomous {
public:
    /**
     * Definitions of the switch and scale positions. Recieved at the start of
     * the match.
     */
    enum class SwitchScalePosition
    {
        LL,              /**< Switch left, Scale left. */
        LR,              /**< Switch left, Scale right. */
        RR,              /**< Switch right, Scale right. */
        RL,              /**< Switch right, Scale left. */
        NOT_YET_RECEIVED /**< The FMS hasn't sent the positions yet. */
    };

    /**
     * Constuct an auutonomous mode.
     * @param disabled The disabled mode.
     * @param drive The drive subsystem.
     * @param intakeAssembly The intakeAssembly subsystem.
     * @param gyro The gyro.
     * @param greylight The GreyLight system.
     */
    Autonomous(Disabled *disabled, Drive *drive, IntakeAssembly *intakeAssembly,
               ADXRS450_Gyro *gyro, GreyLight *greylight);
    virtual ~Autonomous();

    /**
     * Start of autonomous.
     */
    void AutonomousInit();

    /**
     * Loop of autonomous.
     */
    void AutonomousPeriodic();

    /**
     * Stop of autonomous.
     */
    void AutonomousStop();

    /**
     * Get the Switch and Scale position.
     * @return The switch and scale position.
     */
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
