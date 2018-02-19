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
               Claw *claw, Drive *drive, Elevator *elevator, Intake *intake)
        : m_driverJoystick(driver)
        , m_operatorJoystick(codriver)
        , m_claw(claw)
        , m_drive(drive)
        , m_driveMode(DriveMode::Cheesy)
        , m_elevator(elevator)
        , m_intake(intake)
        , m_elevatorMode(ElevatorMode::percentOutput)
        , m_intakeMode(IntakeMode::manual) {
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
        m_drive->HangerDrive(y);
    }

    /**
     * Operator Joystick
     */
    double elevatorManualPower =
        -m_operatorJoystick->GetRawAxis(DualAction::LeftYAxis);

    if (fabs(elevatorManualPower) > 0.1 ||
        m_elevatorMode == ElevatorMode::percentOutput) {
        m_elevatorMode = ElevatorMode::percentOutput;
        m_elevator->SetPower(elevatorManualPower);
    }
    else if (m_elevatorMode == ElevatorMode::zero) {
    }
    else if (m_elevatorMode == ElevatorMode::motionMagic) {
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
            m_elevator->SetPosition(Elevator::GROUND);
            m_intake->Close();
            m_intake->LowerIntake();
            m_intake->RegularPull();
            m_claw->open();
            m_claw->kickOff();
            if ((m_intake->IsCubeIn() && m_elevator->GetPosition() < 2.0) ||
                m_driverJoystick->GetRawButton(DualAction::Start)) {
                m_intakeMode = IntakeMode::switchGrabbing;
                m_intakeModeTimer = GetMsecTime();
            }
            break;
        case IntakeMode::switchGrabbing:
            m_intake->Stop();
            m_intake->Open();
            m_intake->LowerIntake();
            m_claw->grab();
            m_claw->kickOff();
            if ((GetMsecTime() - m_intakeModeTimer) > 300) {
                m_intakeMode = IntakeMode::switchStandby;
            }
            break;
        case IntakeMode::switchStandby:
            m_intake->Stop();
            m_intake->LowerIntake();
            m_claw->grab();
            m_claw->kickOff();
            m_elevatorMode = ElevatorMode::motionMagic;
            m_elevator->SetPosition(Elevator::LOW_GOAL);
            if (m_elevator->GetPosition() > 14.0) {
                m_intake->Close();
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
                    // pto engage
                }
                else {
                }
                break;
            case DualAction::DPadDownVirtBtn:
                if (pressedP) {
                    // pto disengage
                }
                break;
            case DualAction::DPadLeftVirtBtn:
                if (pressedP) {
                }
                break;
            case DualAction::DPadRightVirtBtn:
                if (pressedP) {
                }
                break;
            case DualAction::Start:
                if (pressedP) {
                }
                break;
            case DualAction::Back:

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
                    m_claw->open();
                    m_intake->LowerIntake();
                    m_intake->RegularPull();
                }
                else {
                    m_intake->Stop();
                    m_claw->grab();
                }
                break;
            case DualAction::RightBumper:
                if (pressedP) {
                    m_intakeMode = IntakeMode::manual;
                    m_claw->open();
                    m_intake->Eject();
                }
                else {
                    m_intake->Close();
                    m_claw->open();
                }
                break;
            case DualAction::DPadUpVirtBtn:
                if (pressedP) {
                    m_intakeMode = IntakeMode::manual;
                    m_intake->Open();
                }
                else {
                }
                break;
            case DualAction::DPadDownVirtBtn:
                if (pressedP) {
                    m_intakeMode = IntakeMode::manual;
                    m_intake->Close();
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
                    m_intakeMode = IntakeMode::switchIntaking;
                }
                break;
            case DualAction::Start:
                if (pressedP) {
                    m_elevatorMode = ElevatorMode::zero;
                    m_elevator->Reset();
                }
                break;
        }
    }
};
}
