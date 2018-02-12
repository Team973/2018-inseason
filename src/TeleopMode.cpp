#include "src/TeleopMode.h"
#include "lib/helpers/JoystickHelper.h"

using namespace frc;

namespace frc973 {
Teleop::Teleop(ObservableJoystick *driver, ObservableJoystick *codriver,
               ObservableJoystick *tuning, Claw *claw, Drive *drive,
               Elevator *elevator)
        : m_driverJoystick(driver)
        , m_operatorJoystick(codriver)
        , m_tuningJoystick(tuning)
        , m_claw(claw)
        , m_drive(drive)
        , m_elevator(elevator)
        , m_elevatorMode(ElevatorMode::percentOutput) {
}

Teleop::~Teleop() {
}

void Teleop::TeleopInit() {
    std::cout << "Teleop Start" << std::endl;
    m_driveMode = DriveMode::Openloop;
}

void Teleop::TeleopPeriodic() {
    /**
     * Driver Joystick
     */
    double y = -m_driverJoystick->GetRawAxisWithDeadband(DualAction::LeftYAxis);
    double x =
        -m_driverJoystick->GetRawAxisWithDeadband(DualAction::RightXAxis);
    bool quickturn = m_driverJoystick->GetRawButton(DualAction::LeftBumper);
    if (m_driverJoystick->GetRawButton(DualAction::RightBumper)) {
        x /= 3.0;
        y /= 3.0;
    }

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
                    m_claw->cubeLaunch();
                }
                else {
                }
                break;
            case DualAction::LeftTrigger:
                if (pressedP) {
                    m_claw->kickOn();
                }
                else {
                    m_claw->kickOff();
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
                    m_elevator->SetPosition(Elevator::VAULT);
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
                }
                break;
            case DualAction::LeftTrigger:
                if (pressedP) {
                }
                break;
            case DualAction::RightTrigger:
                if (pressedP) {
                    m_claw->grab();
                }
                else {
                }
                break;
            case DualAction::RightBumper:
                if (pressedP) {
                    m_claw->open();
                }
                else {
                }
                break;
            case DualAction::DPadUpVirtBtn:
                if (pressedP) {
                    // hang fork up
                }
                else {
                }
                break;
            case DualAction::DPadDownVirtBtn:
                if (pressedP) {
                    // hang fork down
                }
                break;
            case DualAction::DPadLeftVirtBtn:
                if (pressedP) {
                    // intake down
                }
                break;
            case DualAction::DPadRightVirtBtn:
                if (pressedP) {
                    // intake up
                }
                break;
            case DualAction::Back:
                if (pressedP) {
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
    }
};
}
