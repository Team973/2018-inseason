#include "src/TestMode.h"
#include "src/auto/profiles/sample_trajectory.h"

using namespace frc;
using namespace sample;

namespace frc973 {
Test::Test(ObservableJoystick *driver, ObservableJoystick *codriver,
           Drive *drive, IntakeAssembly *intakeAssembly, Hanger *hanger,
           GreyLight *greylight)
        : m_driverJoystick(driver)
        , m_operatorJoystick(codriver)
        , m_drive(drive)
        , m_intakeAssembly(intakeAssembly)
        , m_hanger(hanger)
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

    double y = -m_driverJoystick->GetRawAxisWithDeadband(DualAction::LeftYAxis);
    double x =
        -m_driverJoystick->GetRawAxisWithDeadband(DualAction::RightXAxis);
    bool quickturn = m_driverJoystick->GetRawButton(DualAction::RightTrigger);

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
        m_drive->HangerDrive(-y);
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
                }
                break;
            case DualAction::DPadDownVirtBtn:
                if (pressedP) {
                    m_hanger->DisengagePTO();
                }
                break;
            case DualAction::DPadRightVirtBtn:
                if (pressedP) {
                }
                break;
            case DualAction::DPadLeftVirtBtn:
                if (pressedP) {
                    m_driveMode = DriveMode::Hanger;
                    m_hanger->EngagePTO();
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
                    m_intakeAssembly->GoToIntakePosition(
                        IntakeAssembly::IntakePosition::scaleMid);
                }
                break;
            case DualAction::LeftTrigger:
                if (pressedP) {
                    m_intakeAssembly->GoToIntakePosition(
                        IntakeAssembly::IntakePosition::scaleHigh);
                }
                break;
            case DualAction::BtnA:
                if (pressedP) {
                    m_driveMode = DriveMode::Velocity;
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
                    m_drive->PIDDrive(24, 0, Drive::RelativeTo::Now, 0.8);
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
                    m_intakeAssembly->GoToIntakePosition(
                        IntakeAssembly::IntakePosition::vault);
                }
                break;
            case DualAction::DPadDownVirtBtn:
                if (pressedP) {
                    m_intakeAssembly->GoToIntakePosition(
                        IntakeAssembly::IntakePosition::lowGoal);
                }
                break;
            case DualAction::DPadRightVirtBtn:
                if (pressedP) {
                    m_intakeAssembly->GoToIntakePosition(
                        IntakeAssembly::IntakePosition::overBack);
                }
                break;
            case DualAction::DPadLeftVirtBtn:
                if (pressedP) {
                    m_intakeAssembly->GoToIntakePosition(
                        IntakeAssembly::IntakePosition::vault);
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
                }
                else {
                }
                break;
            case DualAction::LeftBumper:
                if (pressedP) {
                }
                else {
                }
                break;
            case DualAction::LeftTrigger:
                if (pressedP) {
                }
                else {
                }
                break;
            case DualAction::BtnA:
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
                else {
                }
                break;
            case DualAction::BtnY:
                if (pressedP) {
                }
                else {
                }
                break;
            case DualAction::Start:
                if (pressedP) {
                    m_hanger->SetForkliftPower(0.5);
                }
                else {
                    m_hanger->SetForkliftPower(0);
                }
                break;
            case DualAction::Back:
                if (pressedP) {
                    m_hanger->SetForkliftPower(-0.5);
                }
                else {
                    m_hanger->SetForkliftPower(0);
                }
                break;
        }
    };
}
}
