#include "src/auto/ForwardAuto.h"
#include "src/auto/AutoRoutine.h"

using namespace frc;

namespace frc973 {
ForwardAuto::ForwardAuto(void) {
}

ForwardAuto::~ForwardAuto(void) {
}

void ForwardAuto::Execute(void) {
    std::cout << "Forward Auto" << std::endl;
    switch (m_autoState) {
        case 0:
            break;
        default:
            break;
    }
}

void ForwardAuto::Reset(void) {
}
};
