#pragma once

#include "WPILib.h"
#include "ctre/Phoenix.h"
#include "lib/managers/CoopTask.h"
#include "lib/logging/LogSpreadsheet.h"
#include "DigitalGlitchFilter.h"

using namespace frc;

namespace frc973 {
class TaskMgr;
class LogSpreadsheet;

class Intake : public CoopTask {
public:
    Intake(TaskMgr *scheduler, LogSpreadsheet *logger,
           DigitalInput *rightCubeSensor, DigitalInput *leftCubeSensor,
           TalonSRX *leftRoller, TalonSRX *rightRoller, Solenoid *cubeClamp);
    virtual ~Intake();

    /*
     * When called, opens the claw arms
     */
    void OpenClaw();

    /*
     * When called, closes claw arms
     */
    void CloseClaw();

    void IntakeCube(double power);
    void EjectCube(double power);
    void HoldCube();
    void StopIntake();

    bool IsCubeIn() const;

    void TaskPeriodic(RobotMode mode);

private:
    TaskMgr *m_scheduler;

    DigitalInput *m_rightCubeSensor;
    DigitalInput *m_leftCubeSensor;
    Solenoid *m_cubeClamp;

    TalonSRX *m_leftRoller;
    TalonSRX *m_rightRoller;

    DigitalGlitchFilter *m_bannerFilter;
};
}
