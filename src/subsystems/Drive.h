/*
 * Drive.h
 *
 *  Created on: January 7, 2018
 *      Author: Kyle
 */
#pragma once

#include "WPILib.h"
#include "Phoenix.h"
#include "src/info/RobotInfo.h"
#include "lib/bases/DriveBase.h"

using namespace frc;
using namespace ctre;

namespace frc973 {
class ArcadeDriveController;
class CheesyDriveController;
class PIDDriveController;
class OpenloopArcadeDriveController;
class AssistedArcadeDriveController;
class StraightDriveController;
class TrapDriveController;
class SplineDriveController;
class LogSpreadsheet;

/*
 * Drive provides an interface to control the drive-base (to do both
 * teleoperated and autonomous movements).  To do this, it makes
 * a bunch of DriveControllers (autonomous pid, autonomous trap,
 * teleop arcade, maybe someday a state space drive controller).  When
 * a command is issued (one of these routines is called), Drive determines
 * which controller is best suited to service that command and makes it
 * the "active" controller.
 *
 *  * DriveBase... calls on the active controller to calculate motor output
 *  * DriveStateProvider... provides the controller with position/angle/speed
       etc
 *  * DrivecontrolSignalReceiver... translates controller output signal to motor
       input signal
 */

class Drive :
        public DriveBase,
        public DriveStateProvider,
        public DriveControlSignalReceiver {
    public:
        Drive(TaskMgr *scheduler, LogSpreadsheet *logger,
              TalonSRX *leftDriveTalonA, VictorSPX *leftDriveVictorB,
              VictorSPX *leftDriveVictorC, TalonSRX *rightDriveTalonA,
              VictorSPX *rightDriveVictorB, VictorSPX *rightDriveVictorC,
              ADXRS450_Gyro *gyro);

        virtual ~Drive();

        /**
         * Zero encoders and gyroscope.
         */
        void Zero();

        /*
         * Sets drive to use the cheesy drive controller if it doesn't already.
         * Also sets the input for the cheesy drive controller.
         *
         * @param throttle Forward-backwards-ness to drive cheesy with
         * @param turn Turn value to drive cheesy with
         * @param isQuickturn Whether quickturn is active
         * @param isHighGear Whether high gear is active
         */
        void CheesyDrive(double throttle, double turn, bool isQuickTurn,
                         bool isHighGear);

        /*
         * Sets drive to use standard arcade drive controller if it doesn't
         *  already
         * Also sets the input for the arcade drive controller.
         *
         * @param throttle Forward-backwards-ness to drive with
         * @param turn Turn value to drive with
         */
        void ArcadeDrive(double throttle, double turn);

        /**
         * Set drive to use the open loop arcade drive controller and sets
         *  powers
         *
         * @param throttle Forward-backwards-ness to drive with
         * @param turn Turn value to drive with
         */
        void OpenloopArcadeDrive(double throttle, double turn);

        /**
         * Set a drive to use the mostly open loop arcade controller plus
         * some gyro velocity help
         *
         * @param throttle Forward-backwards-ness to drive with
         * @param turn Turn value to drive with
         */
        void AssistedArcadeDrive(double throttle, double turn);

        /**
         * Set a target distance to be achieved by pid
         *
         * @param dist Distance in inches to go
         * @param turn Turn value to drive with
         * @param relativity What is that distance metric relative to?
         * @param powerCap
         */
        PIDDriveController *PIDDrive(double dist, double turn,
                                     RelativeTo relativity, double powerCap);

        /**
         * Set a target turn to be achieved by pid
         *
         * @param angle Angle in degrees to go
         * @param relativity What is that angle metric relative to?
         */
        PIDDriveController *PIDTurn(double angle, RelativeTo relativity,
                                    double powerCap);

        /**
         * Set a drive to drive straight
         *
         * @param relativity What is that angle metric relative to?
         * @param throttle Forward-backwards-ness to drive with
         * @param angle Angle in degrees to go
         */
        void DriveStraight(RelativeTo relativity, double throttle,
                           double angle);

        /**
         * Set a drive to use trap profile drive controller
         *
         * @param relativity What is that angle metric relative to?
         * @param dist Distance in inches to go
         * @param angle Angle in degrees to go
         */
        TrapDriveController *TrapDrive(RelativeTo relativity, double dist,
                                       double angle);

        const TrapDriveController *GetTrapDriveController() {
            return m_trapDriveController;
        }

        /**
         * Set a drive to use spline drive controller
         *
         * @param relativity What is that angle metric relative to?
         * @param dist Distance in inches to go
         * @param angle Angle in degrees to go
         */
        SplineDriveController *SplineDrive(RelativeTo relativity, double dist,
                                           double angle);

        const SplineDriveController *GetSplineDriveController(){
            return m_splineDriveController;
        }

        /**
         * All distances given in inches
         * All velocities given in inches/second
         */
        double GetLeftDist() const override;
        double GetRightDist() const override;
        double GetLeftRate() const override;
        double GetRightRate() const override;
        double GetDist() const override;
        double GetRate() const override;

        double GetDriveCurrent() const;

        /**
         * All angles given in degrees
         * All angular rates given in degrees/second
         */
        double GetAngle() const override;
        double GetAngularRate() const override;

        /*
         * Used by the DriveController to set motor values
         *
         * The unit of this command depends on the mode of the controller...
         * If in PercentOutput mode (default), command is from -1.0 to 1.0 and
         *      scales to voltage sent to motors
         * If in Velocity mode, the command is the velocity setpoint in in/sec
         * If in Positon mode, the command is the position setpoint in inches
         *
         * @param mode The ControlMode of the Talons
         * @param left Output to send to leftDriveTalon
         * @param right Output to send to rightDriveTalon
         */
        void SetDriveOutput(phoenix::motorcontrol::ControlMode controlMode,
                            double left, double right);

        void TaskPeriodic(RobotMode mode);
    private:
        LogSpreadsheet *m_logger;

        TalonSRX *m_leftDriveTalonA;
        VictorSPX *m_leftDriveVictorB;
        VictorSPX *m_leftDriveVictorC;
        TalonSRX *m_rightDriveTalonA;
        VictorSPX *m_rightDriveVictorB;
        VictorSPX *m_rightDriveVictorC;

        phoenix::motorcontrol::ControlMode m_controlMode;

        double m_leftDriveOutput;
        double m_rightDriveOutput;

        LogCell *m_leftDriveOutputLog;
        LogCell *m_rightDriveOutputLog;
        LogCell *m_leftVoltageLog;
        LogCell *m_rightVoltageLog;

        double m_leftPosZero;
        double m_rightPosZero;

        ADXRS450_Gyro *m_gyro;
        double m_gyroZero;

        ArcadeDriveController *m_arcadeDriveController;
        CheesyDriveController *m_cheesyDriveController;
        OpenloopArcadeDriveController *m_openloopArcadeDriveController;
        AssistedArcadeDriveController *m_assistedArcadeDriveController;
        PIDDriveController *m_pidDriveController;
        TrapDriveController *m_trapDriveController;
        StraightDriveController *m_straightDriveController;
        SplineDriveController *m_splineDriveController;

        double m_angle;
        double m_angleRate;
        LogCell *m_angleLog;
        LogCell *m_angularRateLog;
        LogCell *m_leftDistLog;
        LogCell *m_leftDistRateLog;
        LogCell *m_rightDistLog;
        LogCell *m_rightDistRateLog;
        LogCell *m_currentLog;
};
}
