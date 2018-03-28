/*
 * TeleopMode.cpp
 *
 *  Created on: January 7, 2018
 *      Authors: Kyle, Chris
 *
 *  Control map available at: https://goo.gl/MrViHA
 */
#include <cmath>
#include "src/TeleopMode.h"
#include "lib/helpers/JoystickHelper.h"

using namespace frc;

namespace frc973 {
Teleop::Teleop(ObservableJoystick *driver, ObservableJoystick *codriver,
               Drive *drive, IntakeAssembly *intakeAssembly, Hanger *hanger,
               GreyLight *greylight)
        : m_driverJoystick(driver)
        , m_operatorJoystick(codriver)
        , m_drive(drive)
        , m_driveMode(DriveMode::Cheesy)
        , m_intakeAssembly(intakeAssembly)
        , m_endGameSignalSent(false)
        , m_enableForkDeploy(false)
        , m_hanger(hanger)
        , m_greyLight(greylight)
        , m_endGameSignal(
              new LightPattern::Flash(END_GAME_RED, NO_COLOR, 50, 15)) {
}

Teleop::~Teleop() {
}

void Teleop::TeleopInit() {
    std::cout << "Teleop Start" << std::endl;
    m_intakeAssembly->SetPosManualInput();
    m_intakeAssembly->EnableCoastMode();
}

void Teleop::TeleopPeriodic() {
    if (!m_endGameSignalSent && Timer::GetMatchTime() < 40) {
        m_endGameSignalSent = true;
        m_endGameSignal->Reset();
        m_greyLight->SetPixelStateProcessor(m_endGameSignal);
    }
    /**
     * Driver Joystick
     */
    double y = -m_driverJoystick->GetRawAxisWithDeadband(DualAction::LeftYAxis);
    double x =
        -m_driverJoystick->GetRawAxisWithDeadband(DualAction::RightXAxis);
    bool quickturn = m_driverJoystick->GetRawButton(DualAction::RightBumper);
    if (m_driverJoystick->GetRawButton(DualAction::RightTrigger)) {
        x /= 3.0;
        y /= 3.0;
    }

    if (m_driveMode == DriveMode::Cheesy) {
        m_drive->CheesyDrive(
            y, x, quickturn,
            false);  // gear set to false until solenoids get set up
    }
    else if (m_driveMode == DriveMode::Hanger) {
        m_hanger->SetHangerPower(y);
    }

    /**
     * Operator Joystick
     */
    double elevatorPosIncInput =
        -m_operatorJoystick->GetRawAxis(DualAction::LeftYAxis);
    double wristPosIncInput = pow(
        -m_operatorJoystick->GetRawAxisWithDeadband(DualAction::RightXAxis), 3);

    if (fabs(elevatorPosIncInput) > 0.25 || fabs(wristPosIncInput) > 0.25) {
        m_intakeAssembly->SetPosManualInput();
    }
}

void Teleop::TeleopStop() {
}

void Teleop::HandleTeleopButton(uint32_t port, uint32_t button, bool pressedP) {
    if (port == DRIVER_JOYSTICK_PORT) {
        switch (button) {
            case DualAction::BtnA:
                if (pressedP) {
                    m_enableForkDeploy = true;
                }
                break;
            case DualAction::LJoystickBtn:
                if (pressedP) {
                }
                else {
                }
                break;
            case DualAction::BtnB:
                if (pressedP) {
                }
                break;
            case DualAction::BtnX:
                if (pressedP) {
                }
                break;
            case DualAction::BtnY:
                if (pressedP) {
                    if (m_enableForkDeploy || Timer::GetMatchTime() < 29) {
                        m_hanger->DeployForks();
                    }
                }
                break;
            case DualAction::LeftBumper:
                if (pressedP) {
                    m_intakeAssembly->DropCube();
                }
                else {
                }
                break;
            case DualAction::LeftTrigger:
                if (pressedP) {
                    m_intakeAssembly->EjectCube();
                }
                else {
                    m_intakeAssembly->StopIntake();
                }
                break;
            case DualAction::RightBumper:
                if (pressedP) {
                    // quickturn (in TeleopPeriodic)
                }
                else {
                }
                break;
            case DualAction::RightTrigger:
                if (pressedP) {
                    // software low gear (in TeleopPeriodic)
                }
                else {
                }
                break;
            case DualAction::DPadUpVirtBtn:
                if (pressedP) {
                    m_driveMode = DriveMode::Hanger;
                    m_hanger->EngagePTO();
                }
                break;
            case DualAction::DPadDownVirtBtn:
                if (pressedP) {
                    m_driveMode = DriveMode::Hanger;
                    m_hanger->DisengagePTO();
                }
                break;
            case DualAction::DPadLeftVirtBtn:
                if (pressedP) {
                }
                break;
            case DualAction::DPadRightVirtBtn:
                if (pressedP) {
                    m_driveMode = DriveMode::Hanger;
                    m_drive->HangerDrive(1.0);
                }
                else {
                    m_drive->HangerDrive(0.0);
                }
                break;
            case DualAction::Start:
                if (pressedP) {
                }
                break;
            case DualAction::Back:
                if (pressedP) {
                }
                break;
        }
    }
    else if (port == OPERATOR_JOYSTICK_PORT) {
        switch (button) {
            case DualAction::BtnY:
                if (pressedP) {
                    m_intakeAssembly->GoToIntakePosition(
                        IntakeAssembly::SCALE_HIGH_PRESET);
                }
                break;
            case DualAction::BtnA:
                if (pressedP) {
                    m_intakeAssembly->GoToIntakePosition(
                        IntakeAssembly::GROUND_PRESET);
                }
                break;
            case DualAction::BtnX:
                if (pressedP) {
                    m_intakeAssembly->GoToIntakePosition(
                        IntakeAssembly::SCALE_LOW_PRESET);
                }
                break;
            case DualAction::BtnB:
                if (pressedP) {
                    m_intakeAssembly->GoToIntakePosition(
                        IntakeAssembly::LOW_GOAL_PRESET);
                }
                else {
                }
                break;
            case DualAction::LeftBumper:
                if (pressedP) {
                    m_intakeAssembly->IntakeCube(-1.0);
                }
                else {
                    m_intakeAssembly->StopIntake();
                }
                break;
            case DualAction::LeftTrigger:
                if (pressedP) {
                    m_intakeAssembly->VaultIntake();
                }
                else {
                    m_intakeAssembly->StopIntake();
                }
                break;
            case DualAction::RightTrigger:
                if (pressedP) {
                    m_intakeAssembly->EjectCube();
                }
                else {
                    m_intakeAssembly->StopIntake();
                }
                break;
            case DualAction::RightBumper:
                if (pressedP) {
                }
                else {
                }
                break;
            case DualAction::DPadUpVirtBtn:
                if (pressedP) {
                    m_hanger->SetForkliftPower(-1.0);
                }
                else {
                    m_hanger->SetForkliftPower(0);
                }
                break;
            case DualAction::DPadDownVirtBtn:
                /*
                    if (pressedP) {
                        m_hanger->SetForkliftPower(-1.0);
                    }
                    else {
                        m_hanger->SetForkliftPower(0);
                    }
                    */
                break;

            case DualAction::DPadLeftVirtBtn:
                if (pressedP) {
                }
                break;
            case DualAction::DPadRightVirtBtn:
                if (pressedP) {
                    m_intakeAssembly->GoToIntakePosition(
                        IntakeAssembly::OVER_BACK_PRESET);
                }
                break;
            case DualAction::Back:
                if (pressedP) {
                    // override banner sensor for switch automated pull
                }
                break;
            case DualAction::Start:
                if (pressedP) {
                    m_intakeAssembly->StartZeroPosition();
                }
                else {
                    m_intakeAssembly->EndZeroPosition();
                }
                break;
        }
    }
};
}
