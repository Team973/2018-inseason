/*
 * JoystickHelper.h
 *
 *  Created on: Sep 13, 2018
 *      Author: Kyle
 */

#pragma once

#include <stdint.h>
#include "lib/managers/CoopTask.h"
#include "lib/helpers/JoystickHelperBase.h"
#include "WPILib.h"
#include "lib/logging/LogSpreadsheet.h"

using namespace frc;

namespace frc973 {

namespace Xbox {
const unsigned int BtnX = 3;
const unsigned int BtnA = 1;
const unsigned int BtnB = 2;
const unsigned int BtnY = 4;
const unsigned int LeftBumper = 5;
const unsigned int RightBumper = 6;
const unsigned int Back = 7;
const unsigned int Start = 8;

const unsigned int LJoystickBtn = 9;
const unsigned int RJoystickBtn = 10;

const unsigned int DPadUpVirtBtn = 11;
const unsigned int DPadDownVirtBtn = 12;
const unsigned int DPadLeftVirtBtn = 13;
const unsigned int DPadRightVirtBtn = 14;

const unsigned int LeftXAxis = 0;
const unsigned int LeftYAxis = 1;
const unsigned int RightXAxis = 4;
const unsigned int RightYAxis = 5;
const unsigned int LeftTriggerAxis = 2;
const unsigned int RightTriggerAxis = 3;
}

class XboxJoystick
        : public CoopTask
        , public Joystick
        , public JoystickHelperBase {
protected:
    Joystick *m_joystick;
    uint32_t m_port;

    /* For observer notification */
    JoystickHelperBase *m_observer;
    DriverStation *m_ds;
    uint32_t m_prevBtn;
    TaskMgr *m_scheduler;
    LogCell *m_logCell;

public:
    /**
     * Create an instance of the XboxJoystick object.  Requires the
     * information to instantiate the underlying WPI-Joystick, as well as
     * references to the scheduler that will run it and the observer that
     * will observe its state.
     *
     * @param port Specifies the joystick port.
     * @param notify Points to the JoystickHelperBase object for button event
     *        notification callback.
     * @param scheduler Points to the task manager this task will run on
     */
    XboxJoystick(uint16_t port, JoystickHelperBase *observer,
                 TaskMgr *scheduler, DriverStation *ds = nullptr);
    ~XboxJoystick();

    /**
     * Register this joystick with a logger so that button state can be logged
     * every time the periodic funciton is called.  Only registers with the
     * first call
     */
    XboxJoystick *RegisterLog(LogSpreadsheet *logger);

    float GetRawAxisWithDeadband(
        int axis, bool fSquared = false,
        double threshold = DEADBAND_INPUT_THRESHOLD) override;

    /**
     * This function is called by the TaskMgr to check and process Joystick
     * button events.
     *
     * @param mode Specifies the CoopTask callback types.
     */
    void TaskPrePeriodic(RobotMode mode) override;
};
}
