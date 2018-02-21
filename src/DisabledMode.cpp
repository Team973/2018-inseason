#include "src/DisabledMode.h"
#include "src/AutonomousMode.h"
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
        , m_greyCam(greyCam) {
}

Disabled::~Disabled() {
}

void Disabled::DisabledInit() {
    std::cout << "Disabled Start" << std::endl;
}

void Disabled::DisabledPeriodic() {
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
                }
                else {
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
};
