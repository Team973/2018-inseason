#include "src/TestMode.h"
#include "src/subsystems/Hanger.h"

using namespace frc;

namespace frc973 {
Test::Test(ObservableJoystick *driver, ObservableJoystick *codriver,
           ObservableJoystick *tuning, Elevator *elevator, Hanger *hanger)
        : m_driverJoystick(driver)
        , m_operatorJoystick(codriver)
        , m_tuningJoystick(tuning)
        , m_elevator(elevator)
        , m_hanger(hanger)
        , m_elevatorMode(ElevatorMode::percentOutput)
        , m_elevatorPosition(0.0) {
}

Test::~Test() {
}

void Test::TestInit() {
    std::cout << "Test Start" << std::endl;
}

void Test::TestPeriodic() {
  if (m_elevatorPosition > 100.0) {
        m_elevatorPosition = 100.0;  // does not allow value to exceed 100.0
    }
    else if (m_elevatorPosition < 0.0) {
        m_elevatorPosition = 0.0;  // does not allow value to be under 0.0
    }

    double y = m_driverJoystick->GetRawAxisWithDeadband(DualAction::LeftYAxis);
    printf("%1.3lf\n", y);
    m_elevatorPosition +=
        1.5 * Util::bound(m_driverJoystick->GetRawAxisWithDeadband(
                              DualAction::RightYAxis),
                          0.0, 100.0);  // Adds on 1.5 every call (20ms) to
                                        // position while bounding it 10

    if (m_elevatorMode == ElevatorMode::percentOutput) {
        m_elevator->SetPower(y);
    }
    else if (m_elevatorMode == ElevatorMode::motionMagic) {
        m_elevator->SetMotionMagic(m_elevatorPosition);
    }
    else if (m_elevatorMode == ElevatorMode::position) {
        m_elevator->SetPosition(m_elevatorPosition);
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
                    m_elevatorMode = ElevatorMode::percentOutput;
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
    else if (port == OPERATOR_JOYSTICK_PORT) {
        switch (button) {
            case DualAction::DPadUpVirtBtn:
                if (pressedP) {
                    m_hanger->SetForkliftPower(0.3);
                }
                else {
                    m_hanger->SetForkliftPower(0);
                }
                break;
            case DualAction::DPadDownVirtBtn:
                if (pressedP) {
                    m_hanger->SetForkliftPower(-0.3);
                }
                else {
                    m_hanger->SetForkliftPower(0);
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
