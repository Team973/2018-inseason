#include "src/TestMode.h"

using namespace frc;

namespace frc973 {
Test::Test(ObservableJoystick *driver, ObservableJoystick *codriver,
           ObservableJoystick *tuning, Drive *drive, Elevator *elevator)
        : m_driverJoystick(driver)
        , m_operatorJoystick(codriver)
        , m_tuningJoystick(tuning)
        , m_drive(drive)
        , m_elevator(elevator)
        , m_elevatorMode(ElevatorMode::percentOutput)
        , m_elevatorPosition(0.0) {
}

Test::~Test() {
}

void Test::TestInit() {
    std::cout << "Test Start" << std::endl;
    m_driveMode = DriveMode::Openloop;
}

void Test::TestPeriodic() {
    double y = -m_driverJoystick->GetRawAxisWithDeadband(DualAction::LeftYAxis);
    double x =
        -m_driverJoystick->GetRawAxisWithDeadband(DualAction::RightXAxis);
    bool quickturn = m_driverJoystick->GetRawButton(DualAction::LeftBumper);
    if (m_driverJoystick->GetRawButton(DualAction::RightBumper)) {
        x /= 3.0;
        y /= 3.0;
    }

    printf("%lf", x);
    printf("%lf", y);

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

    // double y =
    // m_driverJoystick->GetRawAxisWithDeadband(DualAction::LeftYAxis);
    // printf("%1.3lf\n", y);
    // m_elevatorPosition +=
    //     1.5 * Util::bound(m_driverJoystick->GetRawAxisWithDeadband(
    //                           DualAction::RightYAxis),
    //                       0.0, 100.0);  // Adds on 1.5 every call (20ms) to
    //                                     // position while bounding it 10
    //
    // if (m_elevatorMode == ElevatorMode::percentOutput) {
    //     m_elevator->SetPower(y);
    // }
    // else if (m_elevatorMode == ElevatorMode::motionMagic) {
    //     m_elevator->SetMotionMagic(m_elevatorPosition);
    // }
    // else if (m_elevatorMode == ElevatorMode::position) {
    //     m_elevator->SetPosition(m_elevatorPosition);
    // }
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
                    m_elevatorMode = ElevatorMode::motionMagic;
                }
                break;
            case DualAction::DPadRightVirtBtn:
                if (pressedP) {
                    m_elevatorMode = ElevatorMode::position;
                }
                break;
            case DualAction::DPadLeftVirtBtn:
                if (pressedP) {
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
                break;
            case DualAction::LeftTrigger:
                if (pressedP) {
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
                    m_drive->PIDDrive(-50, 0, Drive::RelativeTo::Now, 1);
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
                }
                break;
            case DualAction::DPadDownVirtBtn:
                if (pressedP) {
                }
                break;
            case DualAction::DPadRightVirtBtn:
                if (pressedP) {
                }
                break;
            case DualAction::DPadLeftVirtBtn:
                if (pressedP) {
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
                break;
            case DualAction::LeftTrigger:
                if (pressedP) {
                }
                break;
            case DualAction::BtnA:
                if (pressedP) {
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
    else if (port == TUNING_JOYSTICK_PORT) {
        switch (button) {
            case DualAction::DPadUpVirtBtn:
                if (pressedP) {
                }
                break;
            case DualAction::DPadDownVirtBtn:
                if (pressedP) {
                }
                break;
            case DualAction::DPadRightVirtBtn:
                if (pressedP) {
                }
                break;
            case DualAction::DPadLeftVirtBtn:
                if (pressedP) {
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
                break;
            case DualAction::LeftTrigger:
                if (pressedP) {
                }
                break;
            case DualAction::BtnA:
                if (pressedP) {
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
            case DualAction::Start:
                if (pressedP) {
                }
                break;
            case DualAction::Back:
                if (pressedP) {
                }
                break;
        }
    };
}
}
