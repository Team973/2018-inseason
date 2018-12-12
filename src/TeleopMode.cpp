/**
 * TeleopMode.cpp
 *
 *  Created on: January 7, 2018
 *      Authors: Kyle, Chris
 *
 *  Control map available at: https://goo.gl/MrViHA
 **/
#include <cmath>
#include "src/TeleopMode.h"

using namespace frc;

namespace frc973 {
Teleop::Teleop(ObservableDualActionJoystick *driver,
               ObservableXboxJoystick *codriver, Drive *drive,
               IntakeAssembly *intakeAssembly, Hanger *hanger,
               GreyLight *greylight)
        : m_driverJoystick(driver)
        , m_operatorJoystick(codriver)
        , m_drive(drive)
        , m_driveMode(DriveMode::Cheesy)
        , m_intakeAssembly(intakeAssembly)
        , m_cubeIntakeState(CubeIntakeState::Idle)
        , m_wristControlMode(WristControlMode::ClosedLoop)
        , m_wristControlModeDebouncer(new Debouncer(1.0))
        , m_wristModeSwitchPrevState(false)
        , m_endGameSignalSent(false)
        , m_enableForkDeploy(false)
        , m_hanger(hanger)
        , m_greyLight(greylight)
        , m_endGameSignal(
              new LightPattern::Flash(END_GAME_RED, NO_COLOR, 50, 15))
        , m_wristEmergencySignal(new LightPattern::SolidColor({255, 0, 255}))
        , m_clear(new LightPattern::SolidColor({0, 0, 0})) {
}

Teleop::~Teleop() {
}

void Teleop::TeleopInit() {
    std::cout << "Teleop Start" << std::endl;
    m_intakeAssembly->SetPosManualInput();
    m_intakeAssembly->EnableCoastMode();
    m_intakeAssembly->StopIntake();
    m_hanger->DisengagePTO();
}

void Teleop::TeleopPeriodic() {
    /*DBStringPrintf(DBStringPos::DB_LINE2, "Left Y %1.3f",
                   m_driverJoystick->GetRawAxis(0));
    DBStringPrintf(DBStringPos::DB_LINE3, "Right X %1.3f",
                   m_driverJoystick->GetRawAxis(3));*/

    if (!m_endGameSignalSent && Timer::GetMatchTime() < 40) {
        m_endGameSignalSent = true;
        m_endGameSignal->Reset();
        m_greyLight->SetPixelStateProcessor(m_endGameSignal);
    }
    /**
     * Driver Joystick
     */
    double y = m_driverJoystick->GetRawAxis(DualAction::LeftYAxis);
    double x = m_driverJoystick->GetRawAxis(DualAction::RightXAxis);

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
        // m_hanger->SetHangerPower(y);
    }
    else if (m_driveMode == DriveMode::Limelight) {
        m_drive->LimelightDrive();
    }

    /**
     * Operator Joystick
     */
    double elevatorPosIncInput =
        -m_operatorJoystick->GetRawAxisWithDeadband(Xbox::LeftYAxis);
    double wristPosIncInput =
        pow(-m_operatorJoystick->GetRawAxisWithDeadband(Xbox::RightXAxis), 3);

    if (fabs(elevatorPosIncInput) > 0.25 || fabs(wristPosIncInput) > 0.25) {
        m_intakeAssembly->SetPosManualInput();
    }

    if (fabs(m_operatorJoystick->GetRawAxisWithDeadband(
            Xbox::LeftTriggerAxis)) > 0.4) {
        m_intakeAssembly->GoToIntakePosition(IntakeAssembly::STOW_PRESET);
    }

    switch (m_cubeIntakeState) {
        case CubeIntakeState::Idle:
            if (m_wristControlMode == WristControlMode::OpenLoop) {
                m_greyLight->SetPixelStateProcessor(m_wristEmergencySignal);
            }
            break;
        case CubeIntakeState::SwitchIntaking:
            m_intakeAssembly->RunIntake(-1.0);
            if (m_intakeAssembly->GetClaw()->IsCubeIn()) {
                m_intakeAssembly->HoldCube();
                m_intakeAssembly->HardCloseClaw();
                m_intakeAssembly->Flash();
                m_intakeModeTimer = GetMsecTime();
                m_operatorJoystick->SetRumble(
                    GenericHID::RumbleType::kLeftRumble, 1);
                m_operatorJoystick->SetRumble(
                    GenericHID::RumbleType::kRightRumble, 1);
                m_cubeIntakeState = CubeIntakeState::SwitchIntakeDelay;
            }
            break;
        case CubeIntakeState::SwitchIntakeDelay:
            if (GetMsecTime() - m_intakeModeTimer > 100) {
                m_intakeAssembly->GoToIntakePosition(
                    IntakeAssembly::STOW_PRESET);
                m_intakeModeTimer = GetMsecTime();
                m_operatorJoystick->SetRumble(
                    GenericHID::RumbleType::kLeftRumble, 0);
                m_operatorJoystick->SetRumble(
                    GenericHID::RumbleType::kRightRumble, 0);
                m_cubeIntakeState = CubeIntakeState::Idle;
            }
            break;
        case CubeIntakeState::StopRumble:
            if (GetMsecTime() - m_intakeModeTimer > 500) {
                m_operatorJoystick->SetRumble(
                    GenericHID::RumbleType::kLeftRumble, 0);
                m_operatorJoystick->SetRumble(
                    GenericHID::RumbleType::kRightRumble, 0);
                // m_cubeIntakeState = CubeIntakeState::Idle;
            }
            break;
        case CubeIntakeState::ManualIntaking:
            m_intakeAssembly->RunIntake(-1.0);
            if (m_intakeAssembly->GetClaw()->IsCubeIn()) {
                m_operatorJoystick->SetRumble(
                    GenericHID::RumbleType::kLeftRumble, 1);
                m_operatorJoystick->SetRumble(
                    GenericHID::RumbleType::kRightRumble, 1);
                m_cubeIntakeState = CubeIntakeState::StopRumble;
                m_intakeModeTimer = GetMsecTime();
                m_intakeAssembly->HoldCube();
                m_intakeAssembly->HardCloseClaw();
                m_intakeAssembly->Flash();
            }
            else {
                m_intakeAssembly->SoftCloseClaw();
            }
            break;
    }

    bool wristModeSwitch = m_wristControlModeDebouncer->Update(
        m_operatorJoystick->GetRawButton(Xbox::Back));

    if (wristModeSwitch and !m_wristModeSwitchPrevState) {
        if (m_wristControlMode == WristControlMode::ClosedLoop) {
            m_wristControlMode = WristControlMode::OpenLoop;
            m_greyLight->SetPixelStateProcessor(m_wristEmergencySignal);
            m_intakeAssembly->SetOpenLoopWrist(true);
        }
        else if (m_wristControlMode == WristControlMode::OpenLoop) {
            m_wristControlMode = WristControlMode::ClosedLoop;
            m_intakeAssembly->SetOpenLoopWrist(false);
            m_intakeAssembly->SetPosManualInput();
            m_greyLight->SetPixelStateProcessor(m_clear);
        }
    }

    m_wristModeSwitchPrevState = wristModeSwitch;

    /*if (m_wristControlMode == WristControlMode::OpenLoop) {
        DBStringPrintf(DBStringPos::DB_LINE2, "OPEN LOOP WRIST");
    }
    else {
        DBStringPrintf(DBStringPos::DB_LINE2, "closed loop wrist");
    }*/
}

void Teleop::TeleopStop() {
}

void Teleop::HandlePoofsJoystick(uint32_t port, uint32_t button,
                                 bool pressedP) {
    if (port == DRIVER_JOYSTICK_PORT) {
        switch (button) {
            case PoofsJoysticks::LeftTrigger:
                if (pressedP) {
                    m_intakeAssembly->EjectCube();
                }
                else {
                    m_intakeAssembly->HaltIntake();
                }
                break;
            case PoofsJoysticks::RightTrigger:
                if (pressedP) {
                }
                break;
            case PoofsJoysticks::LeftBumper:
                if (pressedP) {
                    m_intakeAssembly->OpenClaw();
                    m_intakeAssembly->HaltIntake();
                }
                break;
            case PoofsJoysticks::RightBumper:
                if (pressedP) {
                }
                break;
        }
    }
}

void Teleop::HandleXboxJoystick(uint32_t port, uint32_t button, bool pressedP) {
    if (port == OPERATOR_JOYSTICK_PORT) {
        switch (button) {
            case Xbox::BtnY:
                if (pressedP) {
                    m_intakeAssembly->GoToIntakePosition(
                        IntakeAssembly::SCALE_HIGH_PRESET);
                }
                break;
            case Xbox::BtnA:
                if (pressedP) {
                    m_intakeAssembly->GoToIntakePosition(
                        IntakeAssembly::GROUND_PRESET);
                }
                break;
            case Xbox::BtnX:
                if (pressedP) {
                    m_driveMode = DriveMode::Hanger;
                    m_drive->HangerDrive(1.0);
                }
                else {
                    m_drive->HangerDrive(0);
                }
                break;
            case Xbox::BtnB:
                if (pressedP) {
                    m_intakeAssembly->GoToIntakePosition(
                        IntakeAssembly::LOW_GOAL_PRESET);
                }
                break;
            case Xbox::LeftBumper:
                if (pressedP) {
                    m_intakeAssembly->SoftCloseClaw();
                    m_cubeIntakeState = CubeIntakeState::SwitchIntaking;
                    m_intakeAssembly->GoToIntakePosition(
                        IntakeAssembly::GROUND_PRESET);
                }
                else {
                    m_intakeAssembly->HoldCube();
                    m_cubeIntakeState = CubeIntakeState::Idle;
                }
                break;
            case Xbox::LJoystickBtn:
                if (pressedP) {
                }
                break;
            case Xbox::RJoystickBtn:
                if (pressedP) {
                }
                break;
            case Xbox::RightBumper:
                if (pressedP) {
                    m_intakeAssembly->SoftCloseClaw();
                    m_cubeIntakeState = CubeIntakeState::ManualIntaking;
                }
                else {
                    m_intakeAssembly->HoldCube();
                    m_cubeIntakeState = CubeIntakeState::Idle;
                }
                break;
            case Xbox::DPadUpVirtBtn:
                if (pressedP) {
                    m_hanger->SetForkliftPower(-1.0);
                }
                else {
                    m_hanger->SetForkliftPower(0);
                }
                break;
            case Xbox::DPadDownVirtBtn:
                if (pressedP) {
                    if (m_enableForkDeploy || Timer::GetMatchTime() < 29) {
                        m_hanger->DeployForks();
                    }
                }
                break;
            case Xbox::DPadLeftVirtBtn:
                if (pressedP) {
                    m_intakeAssembly->SetModeHanging(true);
                }
                break;
            case Xbox::DPadRightVirtBtn:
                if (pressedP) {
                    m_driveMode = DriveMode::Hanger;
                    m_hanger->EngagePTO();
                }
                break;
            case Xbox::Back:
                if (pressedP) {
                    m_driveMode = DriveMode::Limelight;
                }
                else {
                    m_driveMode = DriveMode::Cheesy;
                }
                break;
            case Xbox::Start:
                if (pressedP) {
                    m_intakeAssembly->StartZeroPosition();
                    m_intakeAssembly->OpenClaw();
                }
                else {
                    m_intakeAssembly->EndZeroPosition();
                }
                break;
        }
    }
}

void Teleop::HandleDualActionJoystick(uint32_t port, uint32_t button,
                                      bool pressedP) {
    if (port == DRIVER_JOYSTICK_PORT) {
        switch (button) {
            case DualAction::BtnA:
                if (pressedP) {
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
                else {
                }
                break;
            case DualAction::BtnX:
                if (pressedP) {
                }
                break;
            case DualAction::BtnY:
                if (pressedP) {
                }
                break;
            case DualAction::LeftBumper:
                if (pressedP) {
                    m_intakeAssembly->HaltIntake();
                    m_intakeAssembly->OpenClaw();
                }
                else {
                }
                break;
            case DualAction::LeftTrigger:
                if (pressedP) {
                    m_intakeAssembly->SlowEjectCube();
                }
                else {
                    m_intakeAssembly->HaltIntake();
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
                    if (m_intakeAssembly->GetElevator()->GetPosition() < 5.0) {
                        m_intakeAssembly->FastEjectCube();
                    }
                    else {
                        m_intakeAssembly->EjectCube();
                    }
                }
                else {
                    m_intakeAssembly->HaltIntake();
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
                    m_driveMode = DriveMode::Cheesy;
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
                }
                break;
            case DualAction::BtnA:
                if (pressedP) {
                }
                break;
            case DualAction::BtnX:
                if (pressedP) {
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
                }
                else {
                    m_intakeAssembly->HoldCube();
                    m_cubeIntakeState = CubeIntakeState::Idle;
                }
                break;
            case DualAction::LeftTrigger:
                if (pressedP) {
                    m_intakeAssembly->SoftCloseClaw();
                    m_cubeIntakeState = CubeIntakeState::ManualIntaking;
                }
                else {
                    m_intakeAssembly->HoldCube();
                    m_cubeIntakeState = CubeIntakeState::Idle;
                }
                break;
            case DualAction::RightTrigger:
                if (pressedP) {
                    m_intakeAssembly->EjectCube();
                }
                else {
                    m_intakeAssembly->HaltIntake();
                }
                break;
            case DualAction::RightBumper:
                if (pressedP) {
                    m_intakeAssembly->HoldCube();
                    m_intakeAssembly->HardCloseClaw();
                    m_intakeModeTimer = GetMsecTime();
                    m_cubeIntakeState = CubeIntakeState::SwitchIntakeDelay;
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
                if (pressedP) {
                    m_enableForkDeploy = true;
                    m_hanger->DeployForks();
                }
                /*
                if (pressedP) {
                    m_intakeAssembly->GoToIntakePosition(
                        IntakeAssembly::STOW_PRESET);
                }
                    */
                break;
            case DualAction::DPadLeftVirtBtn:
                if (pressedP) {
                    m_driveMode = DriveMode::Hanger;
                    m_hanger->EngagePTO();
                }
                break;
            case DualAction::DPadRightVirtBtn:
                if (pressedP) {
                }
                break;
            case DualAction::Back:
                if (pressedP) {
                    // toggle emergency open-loop mode (hold 0.5 seconds)
                }
                break;
            case DualAction::Start:
                if (pressedP) {
                    m_intakeAssembly->StartZeroPosition();
                    m_intakeAssembly->OpenClaw();
                }
                else {
                    m_intakeAssembly->EndZeroPosition();
                }
                break;
        }
    }
};
}
