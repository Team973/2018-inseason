#include "src/auto/ScaleOpposite.h"
#include "src/auto/profiles/rightscaleoppositea_trajectory.h"
#include "src/auto/profiles/leftscaleoppositea_trajectory.h"
#include "src/auto/profiles/rightscaleoppositeb_trajectory.h"
#include "src/auto/profiles/leftscaleoppositeb_trajectory.h"

using namespace frc;
using namespace left_scale_opposite_a;
using namespace right_scale_opposite_a;
using namespace left_scale_opposite_b;
using namespace right_scale_opposite_b;

namespace frc973 {
ScaleOpposite::ScaleOpposite(Drive *drive, Elevator *elevator, Wrist *wrist)
        : m_drive(drive), m_elevator(elevator), m_wrist(wrist), m_autoTimer(0) {
}

ScaleOpposite::~ScaleOpposite() {
}

void ScaleOpposite::Execute(AutoRoutineBase::AutoDirection direction) {
    std::cout << "Scale Auto" << std::endl;
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
            m_wrist->CloseClaw();
            m_autoTimer = GetMsecTime();
            m_autoState++;
            break;
        case 1:
            if (m_drive->GetSplinePercentComplete() > 1.0) {
                if (direction == AutoRoutineBase::AutoDirection::Right) {
                    m_drive->SplineDrive(
                        &left_scale_opposite_b::left_scale_opposite_b,
                        Drive::RelativeTo::Now);
                }
                else if (direction == AutoRoutineBase::AutoDirection::Left) {
                    m_drive->SplineDrive(
                        &right_scale_opposite_b::right_scale_opposite_b,
                        Drive::RelativeTo::Now);
                }
                m_autoState++;
            }
            break;
        case 2:
            if (GetMsecTime() - m_autoTimer > 7000) {
                m_elevator->SetPosition(Elevator::SCALE_HIGH);
                m_autoTimer = GetMsecTime();
                m_autoState++;
            }
            break;
        case 3:
            if (m_drive->GetSplinePercentComplete() > 0.85 ||
                m_drive->OnTarget()) {
                m_autoState++;
            }
            break;
        case 4:
            if (m_drive->GetSplinePercentComplete() > 1.0) {
                m_drive->PIDDrive(-50.0, 0.0, Drive::RelativeTo::Now, 0.8);
                m_autoState++;
            }
            break;
        case 5:
            if (m_drive->OnTarget()) {
                m_elevator->SetPosition(Elevator::GROUND);
                m_autoState++;
            }
        default:
            break;
    }
}

void ScaleOpposite::Reset() {
}
};
