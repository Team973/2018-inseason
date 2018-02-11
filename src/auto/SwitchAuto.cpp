#include "src/auto/SwitchAuto.h"
#include "src/auto/AutoRoutine.h"
using namespace frc;

namespace frc973 {
SwitchAuto::SwitchAuto(void) {
}

SwitchAuto::~SwitchAuto(void) {
}

void SwitchAuto::Execute(void) {
    std::cout << "Switch Auto" << std::endl;
    switch (m_autoState) {
        case 0:
            m_drive->PIDDrive(40.0, 45.0, Drive::RelativeTo::Now, 0.5);
            m_autoState++;
            break;
        case 1:
            if (m_drive->OnTarget()) {
                m_drive->PIDDrive(70.0, -45.0, RelativeTo::Now, 0.5);
            }
            break;
        default:
            break;
    }
}

void SwitchAuto::Reset(void) {
}
};
