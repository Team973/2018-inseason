#include "src/TestMode.h"
#include "src/auto/profiles/sample_trajectory.h"

using namespace frc;
using namespace sample;

namespace frc973 {
Test::Test(ObservableJoystick *driver, ObservableJoystick *codriver,
           Drive *drive, Elevator *elevator, Intake *intake, Claw *claw,
           Hanger *hanger, GreyLight *greylight)
        : m_driverJoystick(driver)
        , m_operatorJoystick(codriver)
        , m_drive(drive)
        , m_elevator(elevator)
        , m_claw(claw)
        , m_intake(intake)
        , m_hanger(hanger)
        , m_elevatorMode(ElevatorMode::percentOutput)
        , m_greylight(greylight)
        , m_flashSignal(
              new LightPattern::Flash({0, 255, 0}, {0, 0, 0}, 50, 50)) {
}

Test::~Test() {
}

void Test::TestInit() {
    std::cout << "Test Start" << std::endl;
    m_driveMode = DriveMode::Openloop;
    m_hanger->DisengagePTO();
}

void Test::TestPeriodic() {
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

    double y = -m_driverJoystick->GetRawAxisWithDeadband(DualAction::LeftYAxis);
    double x =
        -m_driverJoystick->GetRawAxisWithDeadband(DualAction::RightXAxis);
    bool quickturn = m_driverJoystick->GetRawButton(DualAction::LeftBumper);

    if (m_driverJoystick->GetRawButton(DualAction::RightBumper)) {
    }
    x /= 3.0;
    y /= 3.0;

    if (m_driveMode == DriveMode::AssistedArcade) {
        m_drive->AssistedArcadeDrive(y, x);
    }
    else if (m_driveMode == DriveMode::Cheesy) {
        m_drive->CheesyDrive(
            y, x, quickturn,
            false);  // gear set to false until solenoids get set up
    }
    else if (m_driveMode == DriveMode::Hanger) {
        m_drive->HangerDrive(y);
    }
    else if (m_driveMode == DriveMode::Openloop) {
        m_drive->OpenloopArcadeDrive(y, x);
    }
    else if (m_driveMode == DriveMode::Velocity) {
        m_drive->VelocityArcadeDrive(y, x);
    }
    else if (m_driveMode == DriveMode::Spline) {
    }
}

void Test::TestStop() {
}

void Test::HandleTestButton(uint32_t port, uint32_t button, bool pressedP) {
    if (port == DRIVER_JOYSTICK_PORT) {
        switch (button) {
            case DualAction::DPadUpVirtBtn:
                if (pressedP) {
                    m_elevatorMode = ElevatorMode::percentOutput;
                }
                break;
            case DualAction::DPadDownVirtBtn:
                if (pressedP) {
                    m_greylight->SetPixelStateProcessor(m_flashSignal);
                }
                break;
            case DualAction::DPadRightVirtBtn:
                if (pressedP) {
                    m_elevatorMode = ElevatorMode::zero;
                    m_elevator->Reset();
                }
                break;
            case DualAction::DPadLeftVirtBtn:
                if (pressedP) {
                }
                else {
                }
                break;
            case DualAction::RightTrigger:
                if (pressedP) {
                }
                else {
                }
                break;
            case DualAction::RightBumper:
                if (pressedP) {
                    m_driveMode = DriveMode::Spline;
                    m_drive->SplineDrive(&sample::sample,
                                         Drive::RelativeTo::Now);
                }
                else {
                }
                break;
            case DualAction::LeftBumper:
                if (pressedP) {
                    m_elevatorMode = ElevatorMode::motionMagic;
                    m_elevator->SetPosition(Elevator::SCALE_HIGH);
                }
                break;
            case DualAction::LeftTrigger:
                if (pressedP) {
                    m_elevatorMode = ElevatorMode::motionMagic;
                    m_elevator->SetPosition(Elevator::SCALE_MID);
                }
                break;
            case DualAction::BtnA:
                if (pressedP) {
                    m_driveMode = DriveMode::Velocity;
                    m_hanger->DisengagePTO();
                }
                break;
            case DualAction::BtnB:
                if (pressedP) {
                    m_driveMode = DriveMode::Openloop;
                }
                break;
            case DualAction::BtnX:
                if (pressedP) {
                    m_driveMode = DriveMode::AssistedArcade;
                }
                break;
            case DualAction::BtnY:
                if (pressedP) {
                    m_driveMode = DriveMode::Cheesy;
                }
                break;
            case DualAction::Start:
                if (pressedP) {
                    m_driveMode = DriveMode::PID;
                    m_drive->PIDDrive(24, 0, Drive::RelativeTo::Now, 1);
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
            case DualAction::DPadUpVirtBtn:
                if (pressedP) {
                    m_elevatorMode = ElevatorMode::motionMagic;
                    m_elevator->SetPosition(Elevator::GROUND);
                }
                break;
            case DualAction::DPadDownVirtBtn:
                if (pressedP) {
                    m_elevatorMode = ElevatorMode::motionMagic;
                    m_elevator->SetPosition(Elevator::LOW_GOAL);
                }
                break;
            case DualAction::DPadRightVirtBtn:
                if (pressedP) {
                    m_elevatorMode = ElevatorMode::motionMagic;
                    m_elevator->SetPosition(Elevator::SCALE_LOW);
                }
                break;
            case DualAction::DPadLeftVirtBtn:
                if (pressedP) {
                    m_elevatorMode = ElevatorMode::motionMagic;
                    m_elevator->SetPosition(Elevator::VAULT);
                }
                break;
            case DualAction::RightTrigger:
                if (pressedP) {
                    m_claw->cubeLaunch();
                }
                else {
                }
                break;
            case DualAction::RightBumper:
                if (pressedP) {
                    m_claw->push();
                }
                else {
                }
                break;
            case DualAction::LeftBumper:
                if (pressedP) {
                    m_intake->RegularPull();
                    m_intake->LowerIntake();
                    m_claw->open();
                }
                else {
                    m_intake->Stop();
                    m_claw->grab();
                }
                break;
            case DualAction::LeftTrigger:
                if (pressedP) {
                    m_intake->Eject();
                    m_intake->LowerIntake();
                    m_claw->open();
                }
                else {
                    m_intake->Stop();
                    m_claw->grab();
                }
                break;
            case DualAction::BtnA:
                if (pressedP) {
                    m_claw->open();
                }
                else {
                    m_claw->grab();
                }
                break;
            case DualAction::BtnB:
                if (pressedP) {
                    m_claw->drop();
                }
                break;
            case DualAction::BtnX:
                if (pressedP) {
                    m_claw->kickOn();
                }
                else {
                    m_claw->kickOff();
                }
                break;
            case DualAction::BtnY:
                if (pressedP) {
                    m_claw->manualClawOpen();
                }
                else {
                    m_claw->manualClawClosed();
                }
                break;
            case DualAction::Start:
                if (pressedP) {
                }
                break;
            case DualAction::Back:
                if (pressedP) {
                    m_intake->Stop();
                }
                break;
        }
    };
}
}
