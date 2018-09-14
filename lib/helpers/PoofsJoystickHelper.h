/*
 * JoystickHelper.h
 *
 *  Created on: Oct 14, 2015
 *      Author: Andrew
 */

#pragma once

#include <stdint.h>
#include "lib/managers/CoopTask.h"
#include "WPILib.h"
#include "lib/logging/LogSpreadsheet.h"
#include "lib/helpers/JoystickHelper.h"

using namespace frc;

namespace frc973 {

namespace PoofsJoysticks {

const unsigned int LeftXAxis = 26;
const unsigned int LeftYAxis = 27;
const unsigned int RightXAxis = 28;
const unsigned int RightYAxis = 29;

const unsigned int LeftTrigger = 1;
const unsigned int LeftBumper = 2;
const unsigned int RightTrigger = 3;
const unsigned int RightBumper = 4;
}

class PoofsJoystick;

/**
 * This abstract class defines the JoystickObserver object. The object is
 * a callback interface. It is not meant to be created as an object.
 * Instead, it should be inherited by a subclass who needs to be notified
 * on the joystick button events.
 */

class PoofsJoystick
        : public CoopTask
        , public Joystick {
public:
    static constexpr double DEADBAND_INPUT_THRESHOLD = 0.05;
    static constexpr double VIRTUAL_JOYSTICK_THRESHOLD = 0.5;

protected:
    uint32_t m_port;

    /* For observer notification */
    JoystickObserver *m_observer;
    DriverStation *m_ds;
    uint32_t m_prevBtn;
    TaskMgr *m_scheduler;
    LogCell *m_logCell;

    /* For remembering states of sticky buttons */
    bool m_lastLXVal;
    bool m_lastLYVal;
    bool m_lastRXVal;
    bool m_lastRYVal;

public:
    /**
     * Create an instance of the ObservableJoystick object.  Requires the
     * information to instantiate the underlying WPI-Joystick, as well as
     * references to the scheduler that will run it and the observer that
     * will observe its state.
     *
     * @param port Specifies the joystick port.
     * @param notify Points to the JoystickObserver object for button event
     *        notification callback.
     * @param scheduler Points to the task manager this task will run on
     */
    PoofsJoystick(uint16_t port, JoystickObserver *observer, TaskMgr *scheduler,
                  DriverStation *ds = nullptr);
    ~PoofsJoystick();

    /**
     * Register this joystick with a logger so that button state can be logged
     * every time the periodic funciton is called.  Only registers with the
     * first call
     */
    PoofsJoystick *RegisterLog(LogSpreadsheet *logger);

    /**
     * Get the value of the given axis with deadband.
     *
     * @param axis Specifies the axis to get the value of.
     * @param fSquared Specifies whether the joystick input should be squared.
     * @param threshold Specifies the deadband threshold.
     * @param hand Specifies the handedness of the joystick (default to right
     *        hand).
     */
    float GetRawAxisWithDeadband(int axis, bool fSquared = false,
                                 double threshold = DEADBAND_INPUT_THRESHOLD);

    double GetLYAxis();

    double GetLXAxis();

    double GetRYAxis();

    double GetRXAxis();

    bool GetLBumper();

    bool GetRBumper();

    bool GetLTrigger();

    bool GetRTrigger();

    /**
     * Get a bitstring containing the state of *all* buttons on the joystick.
     * Including any 'virtual' buttons like the 'joystick buttons'
     */
    uint32_t GetAllButtons();

    /**
     * This function is called by the TaskMgr to check and process Joystick
     * button events.
     *
     * @param mode Specifies the CoopTask callback types.
     */
    void TaskPrePeriodic(RobotMode mode) override;
};
}
