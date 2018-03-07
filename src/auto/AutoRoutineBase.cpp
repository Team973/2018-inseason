#include "src/auto/AutoRoutineBase.h"

using namespace frc;

namespace frc973 {
AutoRoutineBase::AutoRoutineBase() : m_autoState(0) {
}

AutoRoutineBase::~AutoRoutineBase() {
}

void AutoRoutineBase::Execute(AutoDirection direction) {
    std::cout << "Routine Start" << std::endl;
}

void AutoRoutineBase::Reset() {
    m_autoState = 0;
}
};
