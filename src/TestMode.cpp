#include "src/TestMode.h"
#include "src/auto/profiles/sample_trajectory.h"

using namespace frc;
using namespace sample;

namespace frc973 {
Test::Test(ObservablePoofsJoystick *driver, ObservableXboxJoystick *codriver,
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
    m_intakeMode = IntakeMode::manualPosition;
    m_hanger->DisengagePTO();
}

void Test::TestPeriodic() {
    double elevatorPosIncInput =
        -m_operatorJoystick->GetRawAxisWithDeadband(DualAction::LeftYAxis);
    double wristPosIncInput = pow(
        -m_operatorJoystick->GetRawAxisWithDeadband(DualAction::RightXAxis), 3);

    if (fabs(elevatorPosIncInput) > 0.25 || fabs(wristPosIncInput) > 0.25) {
        m_intakeAssembly->SetPosManualInput();
    }

    if (m_intakeMode == IntakeMode::manualVoltage) {
        double elevatorManualPower =
            -m_operatorJoystick->GetRawAxisWithDeadband(DualAction::LeftYAxis);
        double wristManualPower =
            -m_operatorJoystick->GetRawAxisWithDeadband(DualAction::RightXAxis);

        m_intakeAssembly->SetElevatorManualPower(
            elevatorManualPower + Elevator::ELEVATOR_FEED_FORWARD);

        m_intakeAssembly->SetWristManualPower(wristManualPower);
    }
    else if (m_intakeMode == IntakeMode::manualPosition) {
    }
    else if (m_intakeMode == IntakeMode::motionMagic) {
    }

    double y = -m_driverJoystick->GetRawAxis(DualAction::LeftYAxis);
    double x = -m_driverJoystick->GetRawAxis(DualAction::RightXAxis);
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

void Test::HandlePoofsJoystick(uint32_t port, uint32_t button, bool pressedP) {
    if (port == DRIVER_JOYSTICK_PORT) {
        switch (button) {
            case PoofsJoysticks::LeftTrigger:
                if (pressedP) {
                }
                break;
            case PoofsJoysticks::RightTrigger:
                if (pressedP) {
                }
                break;
            case PoofsJoysticks::LeftBumper:
                if (pressedP) {
                }
                break;
            case PoofsJoysticks::RightBumper:
                if (pressedP) {
                }
                break;
        }
    }
}

void Test::HandleXboxJoystick(uint32_t port, uint32_t button, bool pressedP) {
    if (port == OPERATOR_JOYSTICK_PORT) {
        switch (button) {
            case Xbox::BtnY:
                if (pressedP) {
                }
                break;
            case Xbox::BtnA:
                if (pressedP) {
                }
                break;
            case Xbox::BtnX:
                if (pressedP) {
                }
                break;
            case Xbox::BtnB:
                if (pressedP) {
                }
                else {
                }
                break;
            case Xbox::LeftBumper:
                if (pressedP) {
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
                }
                else {
                }
                break;
            case Xbox::DPadUpVirtBtn:
                if (pressedP) {
                }
                break;
            case Xbox::DPadDownVirtBtn:
                if (pressedP) {
                }
                break;
            case Xbox::DPadLeftVirtBtn:
                if (pressedP) {
                }
                break;
            case Xbox::DPadRightVirtBtn:
                if (pressedP) {
                }
                break;
            case Xbox::Back:
                if (pressedP) {
                }
                break;
            case Xbox::Start:
                if (pressedP) {
                }
                else {
                }
                break;
        }
    }
}

void Test::HandleDualActionJoystick(uint32_t port, uint32_t button,
                                    bool pressedP) {
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
        case DualAction::RightBumper:
            if (pressedP) {
            }
            else {
            }
            break;
        case DualAction::RightTrigger:
            if (pressedP) {
            }
            break;
        case DualAction::DPadUpVirtBtn:
            if (pressedP) {
            }
            break;
        case DualAction::DPadDownVirtBtn:
            if (pressedP) {
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
            if (pressedP) {
            }
            break;
    }
}
}
