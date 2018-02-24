#pragma once

#include "WPILib.h"
#include <iostream>
#include "src/info/RobotInfo.h"
#include "src/auto/AutoRoutineBase.h"
#include "src/auto/NoAuto.h"
#include "src/auto/SwitchAuto.h"
#include "src/auto/ScaleAuto.h"
#include "lib/util/WrapDash.h"
#include "src/DisabledMode.h"
#include "src/Robot.h"
#include "src/subsystems/Drive.h"
#include "src/subsystems/Elevator.h"
#include "src/subsystems/Intake.h"
#include "src/subsystems/Claw.h"

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
        RL
    };

    Autonomous(Disabled *disabled, Drive *drive, Elevator *elevator,
               Intake *intake, Claw *claw, ADXRS450_Gyro *gyro);
    virtual ~Autonomous();

    void AutonomousInit();
    void AutonomousPeriodic();
    void AutonomousStop();

    SwitchScalePosition GetSwitchScalePosition(std::string message);

private:
    enum class AutoRoutine
    {
        noAuto,
        lowGoal,
        highGoal
    };

    NoAuto *m_noAuto;
    SwitchAuto *m_switchAuto;
    ScaleAuto *m_scaleAuto;

    Disabled *m_disabled;

    std::string m_scoringLocations;
    Autonomous::SwitchScalePosition m_switchScalePosition;
    AutoRoutineBase *m_routine;
    AutoRoutineBase::AutoDirection m_direction;

    Drive *m_drive;
    Elevator *m_elevator;
    Intake *m_intake;
    Claw *m_claw;
    ADXRS450_Gyro *m_gyro;
};
};
