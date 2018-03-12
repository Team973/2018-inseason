#include "src/auto/ForwardAuto.h"
using namespace frc;

namespace frc973 {
ForwardAuto::ForwardAuto(Drive *drive) : m_drive(drive) {
}

ForwardAuto::~ForwardAuto() {
}

void ForwardAuto::Execute(AutoRoutineBase::AutoDirection direction) {
    m_drive->PIDDrive(100.0, 0.0, Drive::RelativeTo::Now, 0.8);
}

void ForwardAuto::Reset() {
}
};
