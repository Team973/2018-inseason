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
        , m_intakeMode(IntakeMode::Manual) {
}

Teleop::~Teleop() {
}

void Teleop::TeleopInit() {
    std::cout << "Teleop Start" << std::endl;
    m_intakeMode = IntakeMode::Manual;
    m_intake->Stop();
    m_intake->LowerIntake();
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

    switch (m_intakeMode) {
        case IntakeMode::Manual:
            break;
        case IntakeMode::Intaking:
            m_intake->Close();
            m_intake->RegularPull();
            if (m_intake->IsCubeIn() && m_elevator->GetPosition() < 2) {
                m_intakeMode = IntakeMode::Grabbing;
                m_intakeModeTimer = GetMsecTime();
            }
            break;
        case IntakeMode::Grabbing:
            m_intake->Stop();
            m_intake->Open();
            m_claw->grab();
            if ((GetMsecTime() - m_intakeModeTimer) > 300) {
                m_intakeMode = IntakeMode::Raising;
                m_intakeModeTimer = GetMsecTime();
                m_elevatorMode = ElevatorMode::motionMagic;
                m_elevator->SetPosition(Elevator::LOW_GOAL);
            }
            break;
        case IntakeMode::Raising:
            if (m_elevator->GetPosition() > 14) {
                m_intake->Close();
                m_intakeMode = IntakeMode::Manual;
            }
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
                    m_intakeMode = IntakeMode::Manual;
                    m_claw->drop();
                }
                else {
                }
                break;
            case DualAction::LeftTrigger:
                if (pressedP) {
                    m_intakeMode = IntakeMode::Manual;
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
                else {
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
                    m_intakeMode = IntakeMode::Manual;
                    m_intake->RegularPull();
                    m_intake->LowerIntake();
                    m_claw->open();
                }
                else {
                    m_intake->Stop();
                }
                break;
            case DualAction::LeftTrigger:
                if (pressedP) {
                    m_intakeMode = IntakeMode::Manual;
                    m_intake->Eject();
                    m_intake->LowerIntake();
                    m_claw->open();
                }
                else {
                    m_intake->Stop();
                }
                break;
            case DualAction::RightTrigger:
                if (pressedP) {
                    m_intakeMode = IntakeMode::Manual;
                    m_claw->grab();
                }
                else {
                }
                break;
            case DualAction::RightBumper:
                if (pressedP) {
                    m_intakeMode = IntakeMode::Manual;
                    m_claw->open();
                }
                else {
                }
                break;
            case DualAction::DPadUpVirtBtn:
                if (pressedP) {
                    m_intakeMode = IntakeMode::Manual;
                    m_intake->Open();
                }
                else {
                }
                break;
            case DualAction::DPadDownVirtBtn:
                if (pressedP) {
                    m_intakeMode = IntakeMode::Manual;
                    m_intake->Close();
                }
                break;
            case DualAction::DPadLeftVirtBtn:
                if (pressedP) {
                    m_intakeMode = IntakeMode::Manual;
                    m_intake->LowerIntake();
                }
                break;
            case DualAction::DPadRightVirtBtn:
                if (pressedP) {
                    m_intakeMode = IntakeMode::Manual;
                    m_intake->RaiseIntake();
                }
                break;
            case DualAction::Back:
                if (pressedP) {
                    m_intakeMode = IntakeMode::Intaking;
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
