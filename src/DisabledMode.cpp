#include "src/DisabledMode.h"
#include "src/Robot.h"

using namespace frc;

namespace frc973 {
static const Color DISABLED_RED = {255, 0, 0};
Disabled::Disabled(ObservableJoystick *codriver, IntakeAssembly *intakeAssembly,
                   UsbCamera intakeCamera, UsbCamera forkCamera,
                   VideoSink greyCam, GreyLight *greylight)
        : m_operatorJoystick(codriver)
        , m_startPos(AutoRoutineBase::RobotStartPosition::Center)
        , m_routineMode(AutoRoutineBase::AutoRoutineMode::Sneak)
        , m_intakeCamera(intakeCamera)
        , m_forkCamera(forkCamera)
        , m_greyCam(greyCam)
        , m_greylight(greylight)
        , m_intakeAssembly(intakeAssembly)
        , m_disabledSignal(new LightPattern::SolidColor(DISABLED_RED))
        , m_leftSideSignal(
              new LightPattern::LengthModifier(m_disabledSignal, 12))
        , m_rightSideSignal(
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
    DBStringPrintf(DB_LINE1, "Start %s",
                   RobotStartPosToString(m_startPos, m_routineMode));
}

void Disabled::DisabledStop() {
    m_intakeAssembly->EnableCoastMode();
}

const char *Disabled::RobotStartPosToString(
    AutoRoutineBase::RobotStartPosition position,
    AutoRoutineBase::AutoRoutineMode mode) {
    switch (position) {
        case AutoRoutineBase::RobotStartPosition::Center:
            return "Center";
            break;
        case AutoRoutineBase::RobotStartPosition::Left:
            switch (mode) {
                case AutoRoutineBase::AutoRoutineMode::Sneak:
                    return "LeftSneak";
                    break;
                case AutoRoutineBase::AutoRoutineMode::Scale:
                    return "LeftScale";
                    break;
                default:
                    return "Left";
                    break;
            }
            break;
        case AutoRoutineBase::RobotStartPosition::Right:
            switch (mode) {
                case AutoRoutineBase::AutoRoutineMode::Sneak:
                    return "RightSneak";
                    break;
                case AutoRoutineBase::AutoRoutineMode::Scale:
                    return "RightScale";
                    break;
                default:
                    return "Right";
                    break;
            }
            break;
        default:
            return "Error!";
            break;
    }
}

void Disabled::HandleDisabledButton(uint32_t port, uint32_t button,
                                    bool pressedP) {
    if (port == OPERATOR_JOYSTICK_PORT) {
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
                    m_greyCam.SetSource(m_forkCamera);
                }
                else {
                }
                break;
            case DualAction::LeftTrigger:
                if (pressedP) {
                    m_greyCam.SetSource(m_intakeCamera);
                }
                else {
                }
                break;
            case DualAction::RightBumper:
                if (pressedP) {
                    m_routineMode = AutoRoutineBase::AutoRoutineMode::Sneak;
                }
                break;
            case DualAction::RightTrigger:
                if (pressedP) {
                    m_routineMode = AutoRoutineBase::AutoRoutineMode::Scale;
                }
                break;
            case DualAction::DPadUpVirtBtn:
                if (pressedP) {
                    m_startPos = AutoRoutineBase::RobotStartPosition::Center;
                    m_greylight->SetPixelStateProcessor(m_disabledSignal);
                }
                break;
            case DualAction::DPadDownVirtBtn:
                if (pressedP) {
                }
                break;
            case DualAction::DPadLeftVirtBtn:
                if (pressedP) {
                    m_startPos = AutoRoutineBase::RobotStartPosition::Left;
                    m_greylight->SetPixelStateProcessor(m_leftSideSignal);
                }
                break;
            case DualAction::DPadRightVirtBtn:
                if (pressedP) {
                    m_startPos = AutoRoutineBase::RobotStartPosition::Right;
                    m_greylight->SetPixelStateProcessor(m_rightSideSignal);
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

AutoRoutineBase::AutoRoutineMode Disabled::GetRoutineMode() {
    return m_routineMode;
}
};
