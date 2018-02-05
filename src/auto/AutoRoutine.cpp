#include "src/auto/AutoRoutine.h"

using namespace frc;

namespace frc973 {
AutoRoutine::AutoRoutine() : m_autoState(0) {
}

AutoRoutine::~AutoRoutine() {
}

void AutoRoutine::Execute(void) {
    std::cout << "Routine Start" << std::endl;
}

void AutoRoutine::Reset(void) {
    m_autoState = 0;
}
};
