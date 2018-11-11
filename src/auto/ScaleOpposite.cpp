#include "src/auto/ScaleOpposite.h"
#include "src/auto/profiles/leftscaleopposite_trajectory.h"
#include "src/auto/profiles/rightscaleopposite_trajectory.h"
#include "src/auto/profiles/secondleftscaleoppositebackoff_trajectory.h"
#include "src/auto/profiles/secondleftscaleoppositeintaking_trajectory.h"
#include "src/auto/profiles/secondrightscaleoppositebackoff_trajectory.h"
#include "src/auto/profiles/secondrightscaleoppositeintaking_trajectory.h"
#include "src/auto/profiles/thirdleftscaleoppositebackoff_trajectory.h"
#include "src/auto/profiles/thirdleftscaleoppositeintaking_trajectory.h"
#include "src/auto/profiles/thirdrightscaleoppositebackoff_trajectory.h"
#include "src/auto/profiles/thirdrightscaleoppositeintaking_trajectory.h"
#include "src/auto/profiles/secondleftscalebackoff_trajectory.h"
#include "src/auto/profiles/secondrightscalebackoff_trajectory.h"

using namespace frc;
using namespace left_scale_opposite;
using namespace right_scale_opposite;
using namespace second_left_scale_opposite_intaking;
using namespace second_left_scale_opposite_backoff;
using namespace second_right_scale_opposite_intaking;
using namespace second_right_scale_opposite_backoff;
using namespace third_left_scale_opposite_intaking;
using namespace third_left_scale_opposite_backoff;
using namespace third_right_scale_opposite_intaking;
using namespace third_right_scale_opposite_backoff;
using namespace second_left_scale_backoff;
using namespace second_right_scale_backoff;

namespace frc973 {
ScaleOpposite::ScaleOpposite(Drive *drive, IntakeAssembly *intakeAssembly)
        : m_drive(drive), m_intakeAssembly(intakeAssembly), m_autoTimer(0) {
}

ScaleOpposite::~ScaleOpposite() {
}

void ScaleOpposite::Execute(AutoRoutineBase::AutoDirection direction,
                            std::string scalePos) {
    switch (m_autoState) {
        case 0:
            m_drive->PIDDrive(175.0, 0.0, Drive::RelativeTo::Now, 0.9)
                ->SetVMax(180.0, 360.0);
            m_autoTimer = GetMsecTime();
            m_autoState++;
            break;
        case 1:
            if (GetMsecTime() - m_autoTimer > 2000) {
                if (direction == AutoRoutineBase::AutoDirection::Right) {
                    m_drive->SplineDrive(
                        &left_scale_opposite::left_scale_opposite,
                        Drive::RelativeTo::Now);
                }
                else if (direction == AutoRoutineBase::AutoDirection::Left) {
                    m_drive->SplineDrive(
                        &right_scale_opposite::right_scale_opposite,
                        Drive::RelativeTo::Now);
                }
                m_autoState++;
            }
            break;
        case 2:
            if (GetMsecTime() - m_autoTimer > 6000) {
                m_intakeAssembly->GoToIntakePosition(
                    IntakeAssembly::SCALE_MID_PRESET);
                m_autoTimer = GetMsecTime();
                m_autoState++;
            }
            break;
        case 3:
            if (GetMsecTime() - m_autoTimer > 2000) {
                m_intakeAssembly->FastEjectCube();
                m_autoState++;
            }
            break;
        case 4:
            if (m_drive->GetSplinePercentComplete() > 1.0) {
                m_drive->PIDDrive(-30.0, 0.0, Drive::RelativeTo::Now, 0.8);
                m_autoState++;
            }
            break;
        case 5:
            if (m_drive->OnTarget()) {
                m_intakeAssembly->GoToIntakePosition(
                    IntakeAssembly::GROUND_PRESET);
                m_intakeAssembly->HaltIntake();
                m_autoState++;
            }
        default:
            break;
    }
}

void ScaleOpposite::Reset() {
}
};
