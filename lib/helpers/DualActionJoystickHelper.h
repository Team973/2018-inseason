/*
 * DualActionJoystickHelper.h
 *
 *  Created on: 9/18/18
 *      Author: Andrew
 */

#pragma once

#include <stdint.h>
#include "lib/managers/CoopTask.h"
#include "WPILib.h"
#include "lib/logging/LogSpreadsheet.h"

using namespace frc;

namespace frc973 {

/*
 * Button mapping for the DualAction joystick
 */
namespace DualAction {
/*
 * Standard buttons... shouldn't need any explanation
 */
const unsigned int BtnX = 1;
const unsigned int BtnA = 2;
const unsigned int BtnB = 3;
const unsigned int BtnY = 4;
const unsigned int LeftBumper = 5;
const unsigned int RightBumper = 6;
const unsigned int LeftTrigger = 7;
const unsigned int RightTrigger = 8;
const unsigned int Back = 9;
const unsigned int Start = 10;

/*
 * When you push down on the left and right joystick, that registers
 * as a button press
 */
const unsigned int LJoystickBtn = 11;
const unsigned int RJoystickBtn = 12;

const unsigned int DPadUpVirtBtn = 22;
const unsigned int DPadDownVirtBtn = 23;
const unsigned int DPadLeftVirtBtn = 24;
const unsigned int DPadRightVirtBtn = 25;

/*
 * The following are 'virtual' buttons, one for each joystick axis.
 *  * Virtual buttons default to zero.
 *  * When you push the associated joystick axis above 0.5, it registers
 *  	as pressed
 *  * When you pull the associated joystick axis below -0.5, it registers
 *  	as released
 */
const unsigned int LXAxisVirtButton = 26;
const unsigned int LYAxisVirtButton = 27;
const unsigned int RXAxisVirtButton = 28;
const unsigned int RYAxisVirtButton = 29;
const unsigned int DXAxisVirtButton = 30;
const unsigned int DYAxisVirtButton = 31;

/*
 * Not buttons but the numbers for each axis... can be used with
 * joystick.GetRawAxis
 * DPad axis only return 0.0, -1.0, and 1.0
 */
const unsigned int LeftXAxis = 0;
const unsigned int LeftYAxis = 1;
const unsigned int RightXAxis = 2;
const unsigned int RightYAxis = 3;
const unsigned int DPadXAxis = 4;
const unsigned int DPadYAxis = 5;
}

class ObservableDualActionJoystick;

class DualActionJoystickObserver {
public:
    DualActionJoystickObserver() {
    }
    virtual ~DualActionJoystickObserver() {
    }

    virtual void ObserveDualActionJoystickStateChange(uint32_t port,
                                                      uint32_t button,
                                                      bool newState) = 0;
};

/**
 * This class observes a given joystick and notifies the given callback
 * on any joystick event.  This is particularly useful for catching the
 * *edge* of a button press or release event.  Also lets you use a joystick
 * axis as a button in an easy way.
 */
class ObservableDualActionJoystick
        : public CoopTask
        , public Joystick {
public:
    static constexpr double DEADBAND_INPUT_THRESHOLD =
        0.05; /**< The deadband threshold on the joysticks. */
    static constexpr double VIRTUAL_JOYSTICK_THRESHOLD =
        0.5; /**< The virtual joystick threshold. */

protected:
    uint32_t m_port; /**< The port the joystick is plugged into. */

    /* For observer notification */
    DualActionJoystickObserver
        *m_observer;      /**< The class to notify whenever a change in
       the joystick occurs. */
    DriverStation *m_ds;  /**< The DriverStation operating on.*/
    uint32_t m_prevBtn;   /**< The previous button.*/
    TaskMgr *m_scheduler; /**< The task manager object.*/
    LogCell *m_logCell;   /**< The logger.*/

    /* For remembering states of sticky buttons */
    bool m_lastLXVal; /**< The last left joystick's x axis value */
    bool m_lastLYVal; /**< The last left joystick's y axis value */
    bool m_lastRXVal; /**< The last right joystick's x axis value */
    bool m_lastRYVal; /**< The last right joystick's y axis value */
    bool m_lastDXVal; /**< The last d pad's x axis value */
    bool m_lastDYVal; /**< The last d pad's y axis value */

public:
    /**
     * Create an instance of the ObservableDualActionJoystick object. Requires
     * the information to instantiate the underlying WPI-Joystick, as well as
     * references to the scheduler that will run it and the observer that
     * will observe its state.
     * @param port The joystick port.
     * @param observer The JoystickObserver object for button event notification
     * callback.
     * @param scheduler The task manager this task will run on.
     * @param ds The driver station.
     */
    ObservableDualActionJoystick(uint16_t port,
                                 DualActionJoystickObserver *observer,
                                 TaskMgr *scheduler,
                                 DriverStation *ds = nullptr);
    ~ObservableDualActionJoystick();

    /**
     * Register this joystick with a logger so that button state can be logged
     * every time the periodic funciton is called. Only registers with the
     * first call.
     * @param logger The spreadsheet to log to.
     */
    ObservableDualActionJoystick *RegisterLog(LogSpreadsheet *logger);

    /**
     * Get the value of the given axis with deadband.
     * @param axis Specifies the axis to get the value of.
     * @param fSquared Specifies whether the joystick input should be squared.
     * @param threshold Specifies the deadband threshold.
     */
    float GetRawAxisWithDeadband(int axis, bool fSquared = false,
                                 double threshold = DEADBAND_INPUT_THRESHOLD);

    bool GetDPadUpVirtButton(); /**< Check whether the up button on the d pad is
                       pressed. */
    bool GetDPadDownVirtButton();  /**< Check whether the down button on the d
                          pad is pressed. */
    bool GetDPadLeftVirtButton();  /**< Check whether the left button on the d
                          pad is pressed. */
    bool GetDPadRightVirtButton(); /**< Check whether the right button on the d
                          pad is pressed. */

    /**
     * Pretend the Left X Axis is a button.  By default it is not pressed.
     * If the user pushes it mostly forward (say, more than half way), say
     * that button is pressed.  If the user pulls it mostly backwards (say,
     * more than half way), say that button is released.  If it's anywhere
     * in between, rememember what it last was.
     */

    /**
     * Left X Virtual button.
     * @return Whether the left X virtual button is pressed.
     */
    bool GetLXVirtButton();

    /**
     * Left Y Virtual button.
     * @return Whether the left Y virtual button is pressed.
     */
    bool GetLYVirtButton();

    /**
     * Right X Virtual button.
     * @return Whether the right X virtual button is pressed.
     */
    bool GetRXVirtButton();

    /**
     * Right Y Virtual button.
     * @return Whether the right Y virtual button is pressed.
     */
    bool GetRYVirtButton();

    /**
     * DPad X Virtual button.
     * @return Whether the DPad X virtual button is pressed.
     */
    bool GetDXVirtButton();

    /**
     * DPad Y Virtual button.
     * @return Whether the DPad Y virtual button is pressed.
     */
    bool GetDYVirtButton();

    /**
     * Get a bitstring containing the state of *all* buttons on the joystick.
     * Including any 'virtual' buttons like the 'joystick buttons'.
     * @return The bitstring of all buttons.
     */
    uint32_t GetAllButtons();

    /**
     * This function is called by the TaskMgr to check and process Joystick
     * button events.
     * @param mode The current operating mode of the robot.
     */
    void TaskPrePeriodic(RobotMode mode) override;
};
}
