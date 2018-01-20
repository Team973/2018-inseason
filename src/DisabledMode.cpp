#include "src/DisabledMode.h"
#include "src/AutonomousMode.h"
#include "src/Robot.h"

using namespace frc;

namespace frc973 {
Disabled::Disabled(ObservableJoystick *driver, ObservableJoystick *codriver,
                   ObservableJoystick *tuning)
        : m_routine(SelectedAutoRoutine::none)
        , m_driverJoystick(driver)
        , m_operatorJoystick(codriver)
        , m_tuningJoystick(tuning)
        , m_startPos(2) {
}

Disabled::~Disabled() {
}

void Disabled::DisabledInit() {
    std::cout << "Disabled Start" << std::endl;
}

void Disabled::DisabledPeriodic() {
    DBStringPrintf(DB_LINE0, "Start %d", m_startPos);
}

void Disabled::DisabledStop() {
}

void Disabled::HandleDisabledButton(uint32_t port, uint32_t button,
                                    bool pressedP) {
    if (port == DRIVER_JOYSTICK_PORT) {
        switch (button) {
            case DualAction::BtnA:
                if (pressedP) {
                    m_routine = Disabled::SelectedAutoRoutine::none;
                }
                break;
            case DualAction::BtnB:
                if (pressedP) {
                    m_routine = Disabled::SelectedAutoRoutine::forward;
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
                else {
                }
                break;
            case DualAction::DPadUpVirtBtn:
                if (pressedP) {
                    m_startPos = 1;
                }
                break;
            case DualAction::DPadDownVirtBtn:
                if (pressedP) {
                    m_startPos = 2;
                }
                break;
            case DualAction::DPadLeftVirtBtn:
                if (pressedP) {
                    m_startPos = 3;
                }
                break;
            case DualAction::DPadRightVirtBtn:
                if (pressedP) {
                }
                break;
            default:
                break;
        }
    }
}

const char *Disabled::GetRoutineName() {
    switch (m_routine) {
        case SelectedAutoRoutine::none:
            return "NoAuto";
            break;
        case SelectedAutoRoutine::forward:
            return "ForwardAuto";
            break;
        default:
            break;
    }
    return "Error initializing auto!";
}

Disabled::SelectedAutoRoutine Disabled::GetRoutine() {
    return m_routine;
}

/**
  * @return m_startPos: The starting position of the robot selected
  * by the driver: 1 = left, 2 = center, 3 = right
  **/
int Disabled::GetStartPosition() {
    return m_startPos;
}
};
