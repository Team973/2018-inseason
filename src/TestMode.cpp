#include "src/TestMode.h"

using namespace frc;

namespace frc973 {
Test::Test(ObservableJoystick *driver, ObservableJoystick *codriver,
           ObservableJoystick *tuning, Elevator *elevator)
        : m_driverJoystick(driver)
        , m_operatorJoystick(codriver)
        , m_tuningJoystick(tuning)
        , m_elevator(elevator)
        , m_elevatorMode(ElevatorMode::percentOutput)
        , m_elevatorPosition(0.0) {
}

Test::~Test() {
}

void Test::TestInit() {
    std::cout << "Test Start" << std::endl;
}

void Test::TestPeriodic() {
    if (m_elevator->GetPosition() > 100.0) {
        m_elevator->SetPosition(Elevator::SCALE_HIGH); //does not allow value to exceed 100.0
    }
    else if (m_elevatorPosition < 0.0) {
        m_elevator->SetPosition(Elevator::GROUND);  // does not allow value to be under 0.0
    }

    double y = -m_driverJoystick->GetRawAxis(DualAction::LeftYAxis);
     printf("%1.3lf\n", y);
     m_elevatorPosition += 1.5 * Util::bound(m_driverJoystick->GetRawAxisWithDeadband(DualAction::RightYAxis), 0.0, 100.0); //Adds on 1.5 every call (20ms) to position while bounding it 10

     if (y > 0.1 || y < -0.1 || m_elevatorMode == ElevatorMode::percentOutput) {
         m_elevator->SetPower(y);
     }
     else if (m_elevatorMode == ElevatorMode::zero) {
         m_elevator->Reset();
     }
     else if (m_elevatorMode == ElevatorMode::motionMagic) {
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
                    m_elevatorMode = ElevatorMode::zero;
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
                  m_elevator->SetPosition(Elevator::SCALE_HIGH);
                }
                break;
            case DualAction::LeftTrigger:
                if (pressedP) {
                  m_elevator->SetPosition(Elevator::SCALE_MID);
                }
                break;
            case DualAction::BtnA:
                if (pressedP) {
                  m_elevator->SetPosition(Elevator::GROUND);
                }
                break;
            case DualAction::BtnB:
                if (pressedP) {
                  m_elevator->SetPosition(Elevator::VAULT);
                }
                break;
            case DualAction::BtnX:
                if (pressedP) {
                  m_elevator->SetPosition(Elevator::LOW_GOAL);
                }
                break;
            case DualAction::BtnY:
                if (pressedP) {
                  m_elevator->SetPosition(Elevator::SCALE_LOW);
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
