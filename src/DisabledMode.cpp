#include "src/DisabledMode.h"
#include "src/Robot.h"

using namespace frc;

namespace frc973 {
Disabled::Disabled(ObservableJoystick *driver, ObservableJoystick *codriver)
        : m_driverJoystick(driver)
        , m_operatorJoystick(codriver)
        , m_startPos(RobotStartPosition::Center) {
}

Disabled::~Disabled() {
}

void Disabled::DisabledInit() {
    std::cout << "Disabled Start" << std::endl;
}

void Disabled::DisabledPeriodic() {
    DBStringPrintf(DB_LINE0, "Start %s", RobotStartPosToString(m_startPos));
}

void Disabled::DisabledStop() {
}

const char *Disabled::RobotStartPosToString(RobotStartPosition position) {
    switch (position) {
        case RobotStartPosition::Left:
            return "Left";
            break;
        case RobotStartPosition::Center:
            return "Center";
            break;
        case RobotStartPosition::Right:
            return "Right";
            break;
        default:
            return "Error!";
            break;
    }
}

void Disabled::HandleDisabledButton(uint32_t port, uint32_t button,
                                    bool pressedP) {
    if (port == DRIVER_JOYSTICK_PORT) {
        switch (button) {
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
                    m_startPos = RobotStartPosition::Center;
                }
                break;
            case DualAction::DPadDownVirtBtn:
                if (pressedP) {
                }
                break;
            case DualAction::DPadLeftVirtBtn:
                if (pressedP) {
                    m_startPos = RobotStartPosition::Left;
                }
                break;
            case DualAction::DPadRightVirtBtn:
                if (pressedP) {
                    m_startPos = RobotStartPosition::Right;
                }
                break;
            default:
                break;
        }
    }
}

/**
 * @return m_startPos: The starting position of the robot selected
 * by the driver
 **/
Disabled::RobotStartPosition Disabled::GetStartPosition() {
    return m_startPos;
}
};
