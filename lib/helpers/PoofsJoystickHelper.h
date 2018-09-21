/*
 * PoofsJoystickHelper.h
 *
 *  Created on: 9/13/18
 *      Author: Kyle, Chris Mc
 */

#pragma once

#include <stdint.h>
#include "lib/managers/CoopTask.h"
#include "WPILib.h"
#include "lib/logging/LogSpreadsheet.h"

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

class PoofsJoystick
        : public CoopTask
        , public Joystick {
protected:
    uint32_t m_port;

    /* For observer notification */
    uint32_t m_prevBtn;
    TaskMgr *m_scheduler;
    LogCell *m_logCell;

public:
    /**
     * Create an instance of the ObservableJoystick object.  Requires the
     * information to instantiate the underlying WPI-Joystick, as well as
     * references to the scheduler that will run it and the observer that
     * will observe its state.
     *
     * @param port Specifies the joystick port.
     * @param notify Points to the JoystickHelperBase object for button event
     *        notification callback.
     * @param scheduler Points to the task manager this task will run on
     */
    PoofsJoystick(uint16_t port, TaskMgr *scheduler);

    ~PoofsJoystick();

    /**
     * Register this joystick with a logger so that button state can be logged
     * every time the periodic funciton is called.  Only registers with the
     * first call
     */
    PoofsJoystick *RegisterLog(LogSpreadsheet *logger);

    double GetLYAxis();

    double GetLXAxis();

    double GetRYAxis();

    double GetRXAxis();

    bool GetLBumper();

    bool GetRBumper();

    bool GetLTrigger();

    bool GetRTrigger();

    /**
     * This function is called by the TaskMgr to check and process Joystick
     * button events.
     *
     * @param mode Specifies the CoopTask callback types.
     */
    void TaskPrePeriodic(RobotMode mode) override;
};
}
