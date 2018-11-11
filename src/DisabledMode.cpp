#include "src/DisabledMode.h"
#include "src/Robot.h"

using namespace frc;

namespace frc973 {
static const Color DISABLED_RED = {255, 0, 0};
Disabled::Disabled(ObservablePoofsJoystick *driver,
                   ObservableXboxJoystick *codriver,
                   IntakeAssembly *intakeAssembly, UsbCamera intakeCamera,
                   UsbCamera forkCamera, VideoSink greyCam,
                   GreyLight *greylight)
        : m_driverJoystick(driver)
        , m_operatorJoystick(codriver)
        , m_startPos(AutoRoutineBase::RobotStartPosition::Center)
        , m_routineMode(AutoRoutineBase::AutoRoutineMode::Sneak)
        , m_intakeCamera(intakeCamera)
        , m_forkCamera(forkCamera)
        , m_greyCam(greyCam)
        , m_greylight(greylight)
        , m_intakeAssembly(intakeAssembly)
        , m_disabledSignal(new LightPattern::SolidColor(DISABLED_RED))
        , m_rightSideSignal(
              new LightPattern::LengthModifier(m_disabledSignal, 12))
        , m_leftSideSignal(
              new LightPattern::ReverseModifier(m_rightSideSignal)) {
}

Disabled::~Disabled() {
}

void Disabled::DisabledInit() {
    std::cout << "Disabled Start" << std::endl;
    m_greylight->SetPixelStateProcessor(m_disabledSignal);
    m_intakeAssembly->EnableBrakeMode();
}

void Disabled::DisabledPeriodic() {
    DBStringPrintf(DB_LINE1, "Start %s %s", RobotStartPosToString(m_startPos),
                   AutoRoutineModeToString(m_routineMode));
}

void Disabled::DisabledStop() {
    m_intakeAssembly->EnableCoastMode();
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

const char *Disabled::AutoRoutineModeToString(
    AutoRoutineBase::AutoRoutineMode mode) {
    switch (mode) {
        case AutoRoutineBase::AutoRoutineMode::Sneak:
            return "Sneak";
            break;
        case AutoRoutineBase::AutoRoutineMode::Scale:
            return "Scale";
            break;
        default:
            return "Error!";
            break;
    }
}

void Disabled::HandlePoofsJoystick(uint32_t port, uint32_t button,
                                   bool pressedP) {
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

void Disabled::HandleXboxJoystick(uint32_t port, uint32_t button,
                                  bool pressedP) {
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
                    m_routineMode = AutoRoutineBase::AutoRoutineMode::Sneak;
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
                    m_routineMode = AutoRoutineBase::AutoRoutineMode::Scale;
                }
                else {
                }
                break;
            case Xbox::DPadUpVirtBtn:
                if (pressedP) {
                    m_startPos = AutoRoutineBase::RobotStartPosition::Center;
                    m_greylight->SetPixelStateProcessor(m_disabledSignal);
                }
                break;
            case Xbox::DPadDownVirtBtn:
                if (pressedP) {
                }
                break;
            case Xbox::DPadLeftVirtBtn:
                if (pressedP) {
                    m_startPos = AutoRoutineBase::RobotStartPosition::Left;
                    m_greylight->SetPixelStateProcessor(m_leftSideSignal);
                }
                break;
            case Xbox::DPadRightVirtBtn:
                if (pressedP) {
                    m_startPos = AutoRoutineBase::RobotStartPosition::Right;
                    m_greylight->SetPixelStateProcessor(m_rightSideSignal);
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

void Disabled::HandleDualActionJoystick(uint32_t port, uint32_t button,
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

/**
 * @return m_startPos: The starting position of the robot selected
 * by the driver
 **/
AutoRoutineBase::RobotStartPosition Disabled::GetStartPosition() {
    return m_startPos;
}

AutoRoutineBase::AutoRoutineMode Disabled::GetRoutineMode() {
    return m_routineMode;
}
};
