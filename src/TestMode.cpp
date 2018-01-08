#include "src/TestMode.h"

using namespace frc;

namespace frc973 {
Test::Test()
{
}

Test::~Test() {
}

void Test::TestInit() {
    std::cout << "Test Start" << std::endl;
}

void Test::TestPeriodic(){
}

void Test::TestStop(){
}

void Test::HandleTestButton(uint32_t port, uint32_t button,
                            bool pressedP){
    if (port == DRIVER_JOYSTICK_PORT) {
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
    else if (port == TUNING_JOYSTICK_PORT){
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
