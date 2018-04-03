#include "src/auto/ForwardAuto.h"
#include "src/auto/profiles/rightscaleoppositea_trajectory.h"
#include "src/auto/profiles/leftscaleoppositea_trajectory.h"

using namespace frc;
using namespace left_scale_opposite_a;
using namespace right_scale_opposite_a;

namespace frc973 {
ForwardAuto::ForwardAuto(Drive *drive) : m_drive(drive) {
}

ForwardAuto::~ForwardAuto() {
}

void ForwardAuto::Execute(AutoRoutineBase::AutoDirection direction) {
    switch (m_autoState) {
        case 0:
            if (direction == AutoRoutineBase::AutoDirection::Right) {
                m_drive->SplineDrive(
                    &left_scale_opposite_a::left_scale_opposite_a,
                    Drive::RelativeTo::Now);
            }
            else if (direction == AutoRoutineBase::AutoDirection::Left) {
                m_drive->SplineDrive(
                    &right_scale_opposite_a::right_scale_opposite_a,
                    Drive::RelativeTo::Now);
            }
            m_autoState++;
            break;
    }
}

void ForwardAuto::Reset() {
}
};
