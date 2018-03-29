/*
 * Hanger.h
 *
 *  Created on: January 7, 2018
 *      Author: Kyle
 */
#pragma once

#include "WPILib.h"
#include "Phoenix.h"
#include "lib/managers/CoopTask.h"
#include "lib/logging/LogSpreadsheet.h"
#include "src/info/RobotInfo.h"
#include "src/subsystems/Drive.h"
#include "src/subsystems/Elevator.h"
#include "lib/helpers/GreyLight.h"
#include "lib/pixelprocessors/SolidColor.h"

using namespace frc;
using namespace cs;

namespace frc973 {
class TaskMgr;
class LogSpreadsheet;

class Hanger : public CoopTask {
public:
    const Color HANGER_RED = {255, 0, 0};

    Hanger(TaskMgr *scheduler, LogSpreadsheet *logger, Drive *drive,
           Elevator *elevator, Solenoid *hangerPTO, Solenoid *forkDeploy,
           TalonSRX *forkliftTalon, UsbCamera intakeCamera,
           UsbCamera forkCamera, VideoSink greyCam, GreyLight *greylight);
    virtual ~Hanger();

    /**
     * Engages the hanger PTO, runs drive + elevator motors
     **/
    void EngagePTO();

    /**
     * Disengages the hanger PTO, stops drive + elevator motors
     **/
    void DisengagePTO();

    void DeployForks();

    /**
     * Sets all forklift motors to a determined speed
     * @param power Throttle from the joystick to set as forklift power
     **/
    void SetForkliftPower(double power);

    /**
     * Calls the HangerDriveController to drive the drive motors with PTO
     *Engaged
     * @param power Throttle from the joystick to set as PTO power
     **/
    void SetHangerPower(double power);

    void TaskPeriodic(RobotMode mode);

private:
    TaskMgr *m_scheduler;
    LogSpreadsheet *m_logger;
    Drive *m_drive;
    Elevator *m_elevator;
    Solenoid *m_hangerPTO;
    Solenoid *m_forkDeploy;
    TalonSRX *m_forkliftTalon;

    UsbCamera m_intakeCamera;
    UsbCamera m_forkCamera;
    VideoSink m_greyCam;

    GreyLight *m_greylight;
    LightPattern::SolidColor *m_ptoSignal;
};
}
