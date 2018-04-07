/*
 * CoopMTRobot.h
 *
 *  Created on: Sep 1, 2015
 *      Author: Andrew
 *
 * Functionality pretty similar to WPILIB's Iterative Robot
 * except that this one manages tasks and has a Start and Stop
 * method for each state.
 *
 * A more ideal solution would probably have been to inherit from
 * SimpleRobot and use the same virtual method names as Iterative Robot,
 * but IterativeRobot handles driver station and HAL communication and those
 * protocols are subject to change... this should be more maintainable
 * in the long run.
 */

#pragma once

#include "stdint.h"
#include "WPILib.h"
#include "lib/managers/TaskMgr.h"
#include "lib/util/Util.h"
#include <pthread.h>

#ifndef PROGRAM_NAME
#define PROGRAM_NAME "(unspecified)"
#endif

using namespace frc;

namespace frc973 {

static constexpr int MAXHOSTNAMELEN = 128;

class CoopMTRobot
        : public IterativeRobot
        , public TaskMgr
        , public frc::RobotStateInterface {
public:
    CoopMTRobot();
    virtual ~CoopMTRobot();

    /**
     * Similar to RobotInit in the IterativeRobot class, override Initialize
     * to do any post-constructor initialization.
     */
    virtual void Initialize() {
    }

    /**
     * The following {Disabled,Autonomous,Teleop,Test}{Start,Stop,Continuous}
     * should be overridden to get behavior similar to overriding those
     * functions in Iterative Robot:
     *   - <Mode>Start is called when robot first changes into this mode (like
     * <Mode>Init in IterativeRobot).
     *   - <Mode>Stop is called when robot moves to another mode from <Mode>.
     *   - <Mode>Continuous is called repeatedly every 20ms (like <Mode>Periodic
     * in IterativeRobot).
     *   - <Mode>Start is garaunteed to be called before <Mode>Continuous.
     *   - <Mode>Stop for the previous mode is garaunteed to be called before
     * <Mode>Start from the prevous mode.
     */

    /**
     * DisabledStart is called when robot first changes into this mode (like
     * DisabledInit in IterativeRobot). DisabledStart is garaunteed to be called
     * before DisabledContinuous.
     */
    virtual void DisabledStart() {
    }

    /**
     * DisabledStop is called when robot moves to another mode from Disabled.
     * DisabledStop for the previous mode is garaunteed to be called before
     * <Mode>Start from the prevous mode.
     */
    virtual void DisabledStop() {
    }

    /**
     * DisabledContinuous is called repeatedly every 20ms (like DisabledPeriodic
     * in IterativeRobot).
     */
    virtual void DisabledContinuous() {
    }

    /**
     * AutonomousStart is called when robot first changes into this mode (like
     * AutonomousInit in IterativeRobot). AutonomousStart is garaunteed to be
     * called before AutonomousContinuous.
     */
    virtual void AutonomousStart() {
    }

    /**
     * AutonomousStop is called when robot moves to another mode from
     * Autonomous. AutonomousStop for the previous mode is garaunteed to be
     * called before <Mode>Start from the prevous mode.
     */
    virtual void AutonomousStop() {
    }

    /**
     * AutonomousContinuous is called repeatedly every 20ms (like
     * AutonomousPeriodic in IterativeRobot).
     */
    virtual void AutonomousContinuous() {
    }

    /**
     * TelopStart is called when robot first changes into this mode (like
     * TelopInit in IterativeRobot). TelopStart is garaunteed to be called
     * before TelopContinuous.
     */
    virtual void TeleopStart() {
    }

    /**
     * TeleopStop is called when robot moves to another mode from Teleop.
     * TeleopStop for the previous mode is garaunteed to be called before
     * <Mode>Start from the prevous mode.
     */
    virtual void TeleopStop() {
    }

    /**
     * TeleopContinuous is called repeatedly every 20ms (like TeleopPeriodic in
     * IterativeRobot).
     */
    virtual void TeleopContinuous() {
    }

    /**
     * TestStart is called when robot first changes into this mode (like
     * TestInit in IterativeRobot). TestStart is garaunteed to be called before
     * TestContinuous.
     */
    virtual void TestStart() {
    }

    /**
     * TestStop is called when robot moves to another mode from Test. TestStop
     * for the previous mode is garaunteed to be called before <Mode>Start from
     * the prevous mode.
     */
    virtual void TestStop() {
    }

    /**
     * TestContinuous is called repeatedly every 20ms (like TestPeriodic in
     * IterativeRobot).
     */
    virtual void TestContinuous() {
    }

    /**
     * Called continuously during all robot stages
     */
    virtual void AllStateContinuous() {
    }

protected:
    /**
     * For internal use only.  Children of this object should not try to
     * override these (if they do, they *WILL NOT GET RUN*).
     */

    /**
     * Start the robot program.
     */
    void RobotInit() override;

    /**
     * Stop the previous mode and start Disabled.
     */
    void DisabledInit() override;

    /**
     * Stop the previous mode and start Autonomous.
     */
    void AutonomousInit() override;

    /**
     * Stop the previous mode and start Teleop.
     */
    void TeleopInit() override;

    /**
     * Stop the previous mode and start Test.
     */
    void TestInit() override;

    /**
     * Start the Disabled loop.
     */
    void DisabledPeriodic() override;

    /**
     * Start the Autonomous loop.
     */
    void AutonomousPeriodic() override;

    /**
     * Start the Teleop loop.
     */
    void TeleopPeriodic() override;

    /**
     * Start the Test loop.
     */
    void TestPeriodic() override;

    /**
     * Stop a robot mode.
     * @param toStop The robot mode to stop.
     */
    void ModeStop(RobotMode toStop);

    /**
     * Start a robot mode.
     * @param toStart The robot mode to start.
     */
    void ModeStart(RobotMode toStart);

    /**
     * Return disabled status.
     * @return Whether the robot is disabled or not.
     */
    bool IsDisabled() const override;

    /**
     * Return enabled status.
     * @return Whether the robot is enabled or not.
     */
    bool IsEnabled() const override;

    /**
     * Return teleop status.
     * @return Whether the robot is enabled in teleop or not.
     */
    bool IsOperatorControl() const override;

    /**
     * Return autonomous status.
     * @return Whether the robot is enabled in autonomous or not.
     */
    bool IsAutonomous() const override;

    /**
     * Return test status.
     * @return Whether the robot is enabled in test or not.
     */
    bool IsTest() const override;

private:
    RobotMode m_prevMode;
    mutable pthread_mutex_t m_robotModeMutex;
};
}
