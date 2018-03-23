/*
 * TeleopMode.cpp
 *
 *  Created on: January 7, 2018
 *      Authors: Kyle, Chris
 *
 *  Control map available at: https://goo.gl/MrViHA
 */
#include "src/TeleopMode.h"
#include "lib/helpers/JoystickHelper.h"

using namespace frc;

namespace frc973 {
Teleop::Teleop(ObservableJoystick *driver, ObservableJoystick *codriver,
               Wrist *wrist, Drive *drive, Elevator *elevator, Hanger *hanger,
               GreyLight *greylight)
        : m_driverJoystick(driver)
        , m_operatorJoystick(codriver)
        , m_wrist(wrist)
        , m_drive(drive)
        , m_driveMode(DriveMode::Cheesy)
        , m_elevator(elevator)
        , m_elevatorMode(ElevatorMode::percentOutput)
        , m_intakeMode(IntakeMode::manual)
        , m_endGameSignalSent(false)
        , m_hanger(hanger)
        , m_greyLight(greylight)
        , m_intakeSignal(
              new LightPattern::Flash(INTAKE_GREEN, NO_COLOR, 50, 15))
        , m_endGameSignal(
              new LightPattern::Flash(END_GAME_RED, NO_COLOR, 50, 15)) {
}

Teleop::~Teleop() {
}

void Teleop::TeleopInit() {
    std::cout << "Teleop Start" << std::endl;
    m_intakeMode = IntakeMode::manual;
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
        // m_hanger->SetHangerPower(y);
    }

    /**
     * Operator Joystick
     */
    double elevatorManualPower =
        -m_operatorJoystick->GetRawAxis(DualAction::LeftYAxis);

    if (fabs(elevatorManualPower) > 0.1 ||
        m_elevatorMode == ElevatorMode::percentOutput) {
        m_elevatorMode = ElevatorMode::percentOutput;
        m_elevator->SetPower(elevatorManualPower + ELEVATOR_FEED_FORWARD);
    }
    else if (m_elevatorMode == ElevatorMode::zeroingDown) {
    }
    else if (m_elevatorMode == ElevatorMode::motionMagic) {
    }

    double intakeSpinDirection =
        -m_operatorJoystick->GetRawAxisWithDeadband(DualAction::RightXAxis);

    double intakeControl =
        -m_operatorJoystick->GetRawAxis(DualAction::RightYAxis);

    switch (m_intakeMode) {
        case IntakeMode::manual:
            break;
        case IntakeMode::switchIntaking:
            m_elevatorMode = ElevatorMode::motionMagic;
            m_elevator->SetPosition(Elevator::VAULT);
            if (m_elevator->GetPosition() < 5.0 ||
                m_driverJoystick->GetRawButton(DualAction::Back)) {
                m_intakeMode = IntakeMode::switchTaking;
            }
            break;
        case IntakeMode::switchTaking:
            m_elevator->SetPosition(Elevator::GROUND);
            if (m_elevator->GetPosition() < 2.0) {
                m_intakeModeTimer = GetMsecTime();
                m_intakeMode = IntakeMode::switchGrabbing;
            }
            break;
        case IntakeMode::switchGrabbing:
            if (GetMsecTime() - m_intakeModeTimer > 200.0) {
                m_intakeMode = IntakeMode::switchStandby;
            }
            break;
        case IntakeMode::switchStandby:
            m_elevatorMode = ElevatorMode::motionMagic;
            m_elevator->SetPosition(Elevator::VAULT);
            m_intakeSignal->Reset();
            m_greyLight->SetPixelStateProcessor(m_intakeSignal);
            break;
        case IntakeMode::vaultStart:
            m_elevatorMode = ElevatorMode::motionMagic;
            m_elevator->SetPosition(Elevator::GROUND);
            m_intakeModeTimer = GetMsecTime();
            m_intakeMode = IntakeMode::vaultIntaking;
            break;
        case IntakeMode::vaultIntaking:
            if (m_elevator->GetPosition() < 1.0 &&
                (GetMsecTime() - m_intakeModeTimer) > 300) {
                m_elevatorMode = ElevatorMode::motionMagic;
                m_elevator->SetPosition(Elevator::GROUND);
            }
            break;
        default:
            break;
    }

    SmartDashboard::PutNumber("intake/modes/currentmode", (int)m_intakeMode);
}

void Teleop::TeleopStop() {
}

void Teleop::HandleTeleopButton(uint32_t port, uint32_t button, bool pressedP) {
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
                break;
            case DualAction::BtnX:
                if (pressedP) {
                }
                break;
            case DualAction::BtnY:
                if (pressedP) {
                    m_hanger->DeployForks();
                }
                break;
            case DualAction::LeftBumper:
                if (pressedP) {
                    m_intakeMode = IntakeMode::manual;
                }
                else {
                }
                break;
            case DualAction::LeftTrigger:
                if (pressedP) {
                    m_intakeMode = IntakeMode::manual;
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
                    m_elevatorMode = ElevatorMode::motionMagic;
                    m_elevator->SetPosition(Elevator::SCALE_HIGH);
                }
                break;
            case DualAction::BtnA:
                if (pressedP) {
                    m_elevatorMode = ElevatorMode::motionMagic;
                    m_elevator->SetPosition(Elevator::GROUND);
                }
                break;
            case DualAction::BtnX:
                if (pressedP) {
                    m_elevatorMode = ElevatorMode::motionMagic;
                    m_elevator->SetPosition(Elevator::SCALE_LOW);
                }
                break;
            case DualAction::BtnB:
                if (pressedP) {
                    m_elevatorMode = ElevatorMode::motionMagic;
                    m_elevator->SetPosition(Elevator::LOW_GOAL);
                }
                else {
                }
                break;
            case DualAction::LeftBumper:
                if (pressedP) {
                    m_intakeMode = IntakeMode::switchIntaking;
                }
                else {
                    m_intakeMode = IntakeMode::manual;
                }
                break;
            case DualAction::LeftTrigger:
                if (pressedP) {
                    m_intakeMode = IntakeMode::vaultStart;
                }
                else {
                    m_intakeMode = IntakeMode::manual;
                }
                break;
            case DualAction::RightTrigger:
                if (pressedP) {
                    m_intakeMode = IntakeMode::manual;
                }
                else {
                }
                break;
            case DualAction::RightBumper:
                if (pressedP) {
                    m_intakeMode = IntakeMode::manual;
                }
                else {
                }
                break;
            case DualAction::DPadUpVirtBtn:
                if (pressedP) {
                    m_hanger->SetForkliftPower(1.0);
                }
                else {
                    m_hanger->SetForkliftPower(0);
                }
                break;
            case DualAction::DPadDownVirtBtn:
                if (pressedP) {
                    m_hanger->SetForkliftPower(-1.0);
                }
                else {
                    m_hanger->SetForkliftPower(0);
                }
                break;
            case DualAction::DPadLeftVirtBtn:
                if (pressedP) {
                    m_intakeMode = IntakeMode::manual;
                }
                break;
            case DualAction::DPadRightVirtBtn:
                if (pressedP) {
                    m_intakeMode = IntakeMode::manual;
                }
                break;
            case DualAction::Back:
                if (pressedP) {
                    // override banner sensor for switch automated pull
                }
                break;
            case DualAction::Start:
                if (pressedP) {
                    m_elevatorMode = ElevatorMode::zeroingDown;
                    m_elevator->Reset();
                }
                else {
                    m_elevator->ZeroPosition();
                    m_elevator->SetPower(0.0);
                }
                break;
        }
    }
};
}
