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

/**
 * Hanger subsystem.
 */
class Hanger : public CoopTask {
public:
    const Color HANGER_RED = {255, 0, 0}; /**< The LED color for driver info. */

    /**
     * Construct a hanger.
     * @param scheduler TaskMgr object.
     * @param logger LogSpreadsheet object.
     * @param drive The drive subsystem.
     * @param elevator The elevator subsystem.
     * @param hangerPTO The solenoid to trigger for engaging the hanger PTO.
     * @param forkDeploy The solenoid to trigger for relasing the forks.
     * @param forkliftTalon The Talon that ratchets the forks.
     * @param intakeCamera The front-facing camera.
     * @param forkCamera The backward-facing camera.
     * @param greyCam The camera server.
     * @param greylight The GreyLight instance to control LEDs.
     */
    Hanger(TaskMgr *scheduler, LogSpreadsheet *logger, Drive *drive,
           Elevator *elevator, Solenoid *hangerPTO, Solenoid *forkDeploy,
           TalonSRX *forkliftTalon, UsbCamera intakeCamera,
           UsbCamera forkCamera, VideoSink greyCam, GreyLight *greylight);
    virtual ~Hanger();

    /**
     * Engages the hanger PTO, runs drive and elevator motors.
     */
    void EngagePTO();

    /**
     * Disengages the hanger PTO, stops drive and elevator motors.
     */
    void DisengagePTO();

    /**
     * Releases the forks.
     */
    void DeployForks();

    /**
     * Set all of the forklift motors to a determined speed.
     * @param power The throttle amount from the joystick to set as fork power.
     */
    void SetForkliftPower(double power);

    /**
     * Calls the HangerDriveController to drive the drive motors with PTO
     * engaged.
     * @param power The throttle amount from the joystick to set as PTO power.
     */
    void SetHangerPower(double power);

    /**
     * Continously check hang stuff.
     * @param mode The current robot mode.
     */
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
