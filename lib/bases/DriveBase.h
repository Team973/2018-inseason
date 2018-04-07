/*
 * DriveBase.h
 *
 *  Created on: Oct 29, 2015
 *      Author: Andrew
 */

#pragma once

#include "lib/managers/TaskMgr.h"
#include "lib/managers/CoopTask.h"
#include "lib/util/Util.h"
#include "WPILib.h"
#include "Phoenix.h"

using namespace frc;

namespace frc973 {

/*
 * Interface for a class that determines the current state of the drivetrain.
 */
class DriveStateProvider {
public:
    /**
     *
     */
    DriveStateProvider() {
    }
    virtual ~DriveStateProvider() {
    }

    /**
     * Return the current angle in degrees.
     * @return The current angle.
     */
    virtual double GetAngle() const = 0;

    /**
     * Return the current angular rate in degrees/second.
     * @return The current angular rate.
     */
    virtual double GetAngularRate() const = 0;

    /**
     * Return the current left distance in inches.
     * @return The current left distance.
     */
    virtual double GetLeftDist() const = 0;

    /**
     * Return the current right distance in inches.
     * @return The current right distance.
     */
    virtual double GetRightDist() const = 0;

    /**
     * Return the current left velocity in inches/second.
     * @return The current left velocity.
     */
    virtual double GetLeftRate() const = 0;

    /**
     * Return the current right velocity in inches/second.
     * @return The current right velocity.
     */
    virtual double GetRightRate() const = 0;

    /**
     * Return the current average distance in inches.
     * @return The current average distance.
     */
    virtual double GetDist() const = 0;

    /**
     * Return the current average velocity in inches/second.
     * @return The current average velocity.
     */
    virtual double GetRate() const = 0;
};

/*
 * Interface for a class that can take drive output.
 */
class DriveControlSignalReceiver {
public:
    /**
     * A drive control signal receiver.
     */
    DriveControlSignalReceiver() {
    }
    virtual ~DriveControlSignalReceiver() {
    }

    /**
     * Receive calculated motor powers from a controller.
     * Should only be called from a child of DriveController.
     */

    /**
     * Create a setpoint velocity in inches/second.
     * @param left Left setpoint.
     * @param right Right setpoint.
     */
    virtual void SetDriveOutputIPS(double left, double right) = 0;

    /**
     * Create a setpoint position in inches.
     * @param left Left setpoint.
     * @param right Right setpoint.
     */
    virtual void SetDriveOutputPosInches(double left, double right) = 0;

    /**
     * Create a setpoint voltage.
     * @param left Left setpoint.
     * @param right Right setpoint.
     */
    virtual void SetDriveOutputVBus(double left, double right) = 0;

    /**
     * Set the current limit in amperes.
     * @param limit The desired current limit.
     */
    virtual void ConfigDriveCurrentLimit(double limit) = 0;

    /**
     * Disable the current limiting on the drivetrain.
     */
    virtual void DisableDriveCurrentLimit() = 0;
};

/*
 * Interface for anything that can use an angle provider, a dist provider, and
 * can use those to send some drive output to the DriveOutput. In general there
 * will be two drive controllers: One that calculates output based solely on
 * joystick values and one that calcualtes output based solely on pid.
 */
class DriveController {
public:
    /**
     * A drive controller.
     */
    DriveController() {
    }
    virtual ~DriveController() {
    }

    /**
     * Use the input signals from |angle| and |dist| and calculate some output,
     * then send that output to |out|.
     * @param state The state provider for handling incoming messages.
     * @param out The signal reciever for handling outgoing messages.
     */
    virtual void CalcDriveOutput(DriveStateProvider *state,
                                 DriveControlSignalReceiver *out) = 0;

    /**
     * Checks with the current controller to see if we are on target. If there
     * is no controller currently selected, just return false.
     * @return Whether the current controller things are done.
     */
    virtual bool OnTarget() = 0;

    /**
     * Start the drive controller.
     * @param out The signal reciever for handling outgoing messages.
     */
    virtual void Start(DriveControlSignalReceiver *out) {
    }

    /**
     * Stop the drive controller.
     * @param out The signal reciever for handling outgoing messages.
     */
    virtual void Stop(DriveControlSignalReceiver *out) {
    }
};

/**
 * Base class for a robot drive.  DriveBase keeps track of one DriveController
 * and uses it to calculate drive output, then drives the motors with those
 * calculated values. CoopTask handles calling TaskPostPeriodic once a cycle.
 */
class DriveBase : public CoopTask {
public:
    /**
     * Creates a new DriveBase Object.  The DriveBase object stores a drive
     * controller (an object capable of calculating motor outputs) and uses it
     * to calculate drive outputs, then drive those drive outputs.
     * @param scheduler
     * @param out The signal reciever for handling outgoing messages.
     * @param state The state provider for handling incoming messages.
     * @param controller The drive controller for hangling movements.
     */
    DriveBase(TaskMgr *scheduler, DriveControlSignalReceiver *out,
              DriveStateProvider *state, DriveController *controller = nullptr);
    virtual ~DriveBase();

    /**
     * When making calls to PID-like-commands, parameters can be relative to the
     * world (Absolute), relative to the current position (Now), or relative to
     * the current setpoint (SetPoint).
     */
    enum RelativeTo
    {
        Absolute, /**< Relative to the world */
        Now,      /**< Relative to the current position */
        SetPoint  /**< Relative to the current setpoint */
    };

    /**
     * Get input from the currently active DriveController. This method comes
     * from CoopTask and is called automatically once a cycle by m_scheduler.
     * @param mode The current operating mode of the robot.
     */
    void TaskPostPeriodic(RobotMode mode) override;

    /**
     * Change the DriveController currently active.
     * @param controller The drive controller for hangling movements.
     */
    void SetDriveController(DriveController *controller);

    /**
     * Checks with the current controller to see if we are on target. If there
     * is no controller currently selected, just return false.
     * @return Whether the current controller things are done.
     */
    bool OnTarget();

protected:
    TaskMgr *m_scheduler;
    DriveControlSignalReceiver *m_driveOutput;

private:
    DriveStateProvider *m_stateProvider;
    DriveController *m_controller;
};
}
