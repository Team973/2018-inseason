#include "src/auto/ForwardAuto.h"
#include "src/auto/AutoRoutine.h"

using namespace frc;

namespace frc973 {
ForwardAuto::ForwardAuto(Drive *drive) : m_drive(drive) {
}

ForwardAuto::~ForwardAuto(void) {
}

void ForwardAuto::Execute(void) {
    std::cout << "Forward Auto" << std::endl;
    switch (m_autoState) {
        case 0:
            printf("Drive Forward\n");
            m_drive->PIDDrive(140.0, 0.0, Drive::RelativeTo::Now, 0.5);
            m_autoState++;
            break;
        default:
            break;
    }
}

void ForwardAuto::Reset(void) {
    printf("Forward Auto Reset\n");
}
};
