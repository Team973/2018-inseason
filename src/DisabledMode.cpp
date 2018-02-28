#include "src/DisabledMode.h"
#include "src/Robot.h"

using namespace frc;

namespace frc973 {
Disabled::Disabled(ObservableJoystick *driver, ObservableJoystick *codriver,
                   UsbCamera intakeCamera, UsbCamera forkCamera,
                   VideoSink greyCam)
        : m_routine(SelectedAutoRoutine::none)
        , m_driverJoystick(driver)
        , m_operatorJoystick(codriver)
        , m_intakeCamera(intakeCamera)
        , m_forkCamera(forkCamera)
        , m_greyCam(greyCam)
        , m_startPos(AutoRoutineBase::RobotStartPosition::Center) {
}

Disabled::~Disabled() {
}

void Disabled::DisabledInit() {
    std::cout << "Disabled Start" << std::endl;
}

void Disabled::DisabledPeriodic() {
    DBStringPrintf(DB_LINE1, "Start %s", RobotStartPosToString(m_startPos));
}

void Disabled::DisabledStop() {
}

const char *Disabled::RobotStartPosToString(
    AutoRoutineBase::RobotStartPosition position) {
    switch (position) {
        case AutoRoutineBase::RobotStartPosition::Left:
            return "Left";
            break;
        case AutoRoutineBase::RobotStartPosition::Center:
            return "Center";
            break;
        case AutoRoutineBase::RobotStartPosition::Right:
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
                    printf("Setting fork camera\n");
                    m_greyCam.SetSource(m_forkCamera);
                }
                else {
                }
                break;
            case DualAction::LeftTrigger:
                if (pressedP) {
                    printf("Setting intake camera\n");
                    m_greyCam.SetSource(m_intakeCamera);
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
                    m_startPos = AutoRoutineBase::RobotStartPosition::Center;
                }
                break;
            case DualAction::DPadDownVirtBtn:
                if (pressedP) {
                }
                break;
            case DualAction::DPadLeftVirtBtn:
                if (pressedP) {
                    m_startPos = AutoRoutineBase::RobotStartPosition::Left;
                }
                break;
            case DualAction::DPadRightVirtBtn:
                if (pressedP) {
                    m_startPos = AutoRoutineBase::RobotStartPosition::Right;
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
AutoRoutineBase::RobotStartPosition Disabled::GetStartPosition() {
    return m_startPos;
}
};
