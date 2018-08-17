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

/**
 * Claw Subsystem.
 */
class Claw : public CoopTask {
public:
    /**
     * Construct a claw.
     * @param scheduler TaskMgr object.
     * @param logger LogSpreadsheet object.
     * @param rightCubeSensor The right cube banner sensor.
     * @param leftCubeSensor The left cube banner sensor.
     * @param leftRoller The Talon for left intake.
     * @param rightRoller The Talon for right intake.
     * @param cubeClamp The solenoid for cube clamp.
     * @param cubeSpring The solenoid for the cube spring.
     */
    Claw(TaskMgr *scheduler, LogSpreadsheet *logger,
         DigitalInput *rightCubeSensor, DigitalInput *leftCubeSensor,
         TalonSRX *leftRoller, TalonSRX *rightRoller, Solenoid *cubeClamp,
         Solenoid *cubeSpring);
    virtual ~Claw();

    /**
     * Opens the claw arms
     */
    void OpenClaw();

    /**
     * Close the claw arms with little pressure.
     */
    void SoftCloseClaw();

    /**
     * Close the claw arms with more pressure.
     */
    void HardCloseClaw();

    /**
     * Runs the intake forward at a given power.
     * @param power Percentage of power, from -1.0 to 1.0.
     */
    void RunIntake(double power);

    /**
     * Runs the intake backwards at a given power.
     * @param power Percentage of power, from -1.0 to 1.0.
     */
    void EjectCube(double power);

    /**
     * Runs the intake forward at -0.15 to hold the cube in.
     */
    void HoldCube();

    /**
     * Sets the intake to 0.0.
     */
    void StopIntake();

    /**
     * True/false if the cube is in.
     * @return Is cube in?
     */
    bool IsCubeIn() const;

    /**
     * Periodically update information about the claw.
     * @param mode The current robot mode.
     */
    void TaskPeriodic(RobotMode mode);

private:
    TaskMgr *m_scheduler;

    DigitalInput *m_rightCubeSensor;
    DigitalInput *m_leftCubeSensor;

    Solenoid *m_cubeClamp;
    Solenoid *m_cubeSpring;

    TalonSRX *m_leftRoller;
    TalonSRX *m_rightRoller;

    DigitalGlitchFilter *m_bannerFilter;
};
}
