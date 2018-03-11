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

static bool g_hangingSignal = false;

Teleop::Teleop(ObservableJoystick *driver, ObservableJoystick *codriver,
               Claw *claw, Drive *drive, Elevator *elevator, Intake *intake,
               Hanger *hanger, GreyLight *greylight)
        : m_driverJoystick(driver)
        , m_operatorJoystick(codriver)
        , m_claw(claw)
        , m_drive(drive)
        , m_driveMode(DriveMode::Cheesy)
        , m_elevator(elevator)
        , m_intake(intake)
        , m_elevatorMode(ElevatorMode::percentOutput)
        , m_intakeMode(IntakeMode::manual)
        , m_hanger(hanger)
        , m_greyLight(greylight)
        , m_intakeSignal(
              new LightPattern::Flash({0, 255, 0}, {0, 0, 0}, 50, 15))
        , m_endGameSignal(
              new LightPattern::Flash({255, 0, 0}, {0, 0, 0}, 50, 15)) {
}

Teleop::~Teleop() {
}

void Teleop::TeleopInit() {
    std::cout << "Teleop Start" << std::endl;
    m_intakeMode = IntakeMode::manual;
    m_intake->Stop();
    m_intake->LowerIntake();
    m_intake->Close();
}

void Teleop::TeleopPeriodic() {
    if (!g_hangingSignal && Timer::GetMatchTime() < 40) {
        g_hangingSignal = true;
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

    if (fabs(intakeSpinDirection) > 0.5) {
        m_intake->SpinCube(intakeSpinDirection);
    }

    double intakeControl =
        -m_operatorJoystick->GetRawAxis(DualAction::RightYAxis);

    if (intakeControl > 0.8) {
        m_intakeMode = IntakeMode::manual;
        m_intake->RaiseIntake();
    }
    else if (intakeControl < -0.8) {
        m_intakeMode = IntakeMode::manual;
        m_intake->LowerIntake();
    }

    switch (m_intakeMode) {
        case IntakeMode::manual:
            break;
        case IntakeMode::switchIntaking:
            m_elevatorMode = ElevatorMode::motionMagic;
            m_elevator->SetPosition(Elevator::VAULT);
            m_intake->Close();
            m_intake->LowerIntake();
            m_intake->RegularPull();
            m_claw->open();
            m_claw->kickOff();
            if ((m_intake->IsCubeIn() && m_elevator->GetPosition() < 5.0) ||
                m_driverJoystick->GetRawButton(DualAction::Back)) {
                m_intakeMode = IntakeMode::switchTaking;
            }
            break;
        case IntakeMode::switchTaking:
            m_elevator->SetPosition(Elevator::GROUND);
            m_intake->Stop();
            m_intake->LowerIntake();
            m_claw->kickOff();
            if (m_elevator->GetPosition() < 2.0) {
                m_claw->grab();
                m_intakeModeTimer = GetMsecTime();
                m_intakeMode = IntakeMode::switchGrabbing;
            }
            break;
        case IntakeMode::switchGrabbing:
            if (GetMsecTime() - m_intakeModeTimer > 200.0) {
                m_intake->Open();
                m_intakeMode = IntakeMode::switchStandby;
            }
            break;
        case IntakeMode::switchStandby:
            m_intake->Stop();
            m_intake->LowerIntake();
            m_claw->grab();
            m_claw->kickOff();
            m_elevatorMode = ElevatorMode::motionMagic;
            m_elevator->SetPosition(Elevator::VAULT);
            m_intakeSignal->Reset();
            m_greyLight->SetPixelStateProcessor(m_intakeSignal);
            m_intakeMode = IntakeMode::switchRaising;
            break;
        case IntakeMode::switchRaising:
            if (m_elevator->GetPosition() > 2.0) {
                m_intake->Open();
            }
            break;
        case IntakeMode::vaultStart:
            m_claw->grab();
            m_claw->kickOff();
            m_elevatorMode = ElevatorMode::motionMagic;
            m_elevator->SetPosition(Elevator::GROUND);
            m_intake->Stop();
            m_intake->Close();
            m_intake->LowerIntake();
            m_intakeModeTimer = GetMsecTime();
            m_intakeMode = IntakeMode::vaultIntaking;
            break;
        case IntakeMode::vaultIntaking:
            if (m_elevator->GetPosition() < 1.0 &&
                (GetMsecTime() - m_intakeModeTimer) > 300) {
                m_elevatorMode = ElevatorMode::motionMagic;
                m_elevator->SetPosition(Elevator::GROUND);
                m_intake->RegularPull();
                m_intake->Close();
                m_intake->LowerIntake();
                m_claw->grab();
                m_claw->kickOff();
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
                }
                break;
            case DualAction::LeftBumper:
                if (pressedP) {
                    m_intakeMode = IntakeMode::manual;
                    m_claw->drop();
                }
                else {
                }
                break;
            case DualAction::LeftTrigger:
                if (pressedP) {
                    m_intakeMode = IntakeMode::manual;
                    m_claw->cubeLaunch();
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
                    m_intake->Stop();
                }
                break;
            case DualAction::LeftTrigger:
                if (pressedP) {
                    m_intakeMode = IntakeMode::vaultStart;
                }
                else {
                    m_intakeMode = IntakeMode::manual;
                    m_intake->Stop();
                }
                break;
            case DualAction::RightTrigger:
                if (pressedP) {
                    m_intakeMode = IntakeMode::manual;
                    m_intake->RegularPull();
                    m_intake->Close();
                }
                else {
                    m_intake->Stop();
                }
                break;
            case DualAction::RightBumper:
                if (pressedP) {
                    m_intakeMode = IntakeMode::manual;
                    m_intake->Eject();
                    m_intake->Close();
                    m_claw->open();
                }
                else {
                    m_intake->Stop();
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
                    m_intake->LowerIntake();
                }
                break;
            case DualAction::DPadRightVirtBtn:
                if (pressedP) {
                    m_intakeMode = IntakeMode::manual;
                    m_intake->RaiseIntake();
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
