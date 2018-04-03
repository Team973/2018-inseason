#include "src/auto/ScaleOpposite.h"
#include "src/auto/profiles/secondleftscaleoppositebackoff_trajectory.h"
#include "src/auto/profiles/secondleftscaleoppositeintaking_trajectory.h"
#include "src/auto/profiles/secondrightscaleoppositebackoff_trajectory.h"
#include "src/auto/profiles/secondrightscaleoppositeintaking_trajectory.h"
#include "src/auto/profiles/thirdleftscaleoppositebackoff_trajectory.h"
#include "src/auto/profiles/thirdleftscaleoppositeintaking_trajectory.h"
#include "src/auto/profiles/thirdrightscaleoppositebackoff_trajectory.h"
#include "src/auto/profiles/thirdrightscaleoppositeintaking_trajectory.h"

using namespace frc;
using namespace left_scale;
using namespace right_scale;
using namespace second_left_scale_opposite_intaking;
using namespace second_left_scale_opposite_backoff;
using namespace second_right_scale_opposite_intaking;
using namespace second_right_scale_opposite_backoff;
using namespace third_left_scale_opposite_intaking;
using namespace third_left_scale_opposite_backoff;
using namespace third_right_scale_opposite_intaking;
using namespace third_right_scale_opposite_backoff;

namespace frc973 {
ScaleOpposite::ScaleOpposite(Drive *drive, IntakeAssembly *intakeAssembly)
        : m_drive(drive), m_intakeAssembly(intakeAssembly), m_autoTimer(0) {
}

ScaleOpposite::~ScaleOpposite() {
}

void ScaleOpposite::Execute(AutoRoutineBase::AutoDirection direction) {
    std::cout << "Scale Auto" << std::endl;
    switch (m_autoState) {
        case 0:
            if (direction == AutoRoutineBase::AutoDirection::Left) {
                m_drive->SplineDrive(&left_scale_opposite::left_scale_opposite,
                                     Drive::RelativeTo::Now);
            }
            else if (direction == AutoRoutineBase::AutoDirection::Right) {
                m_drive->SplineDrive(
                    &right_scale_opposite::right_scale_opposite,
                    Drive::RelativeTo::Now);
            }
            m_autoTimer = GetMsecTime();
            m_autoState++;
            break;
        case 1:
            if (m_drive->GetSplinePercentComplete() > 0.7) {
                m_intakeAssembly->GoToIntakePosition(
                    IntakeAssembly::OVER_BACK_PRESET);
                m_autoTimer = GetMsecTime();
                m_autoState++;
            }
            break;
        case 2:
            if (m_drive->OnTarget() ||
                m_drive->GetSplinePercentComplete() > 0.9) {
                m_intakeAssembly->FastEjectCube();
                m_autoTimer = GetMsecTime();
                m_autoState++;
            }
            break;
        case 3:
            if (m_drive->OnTarget()) {
                m_intakeAssembly->GoToIntakePosition(
                    IntakeAssembly::GROUND_PRESET);
                m_intakeAssembly->OpenClaw();
                m_intakeAssembly->RunIntake(-1.0);
                if (direction == AutoRoutineBase::AutoDirection::Left) {
                    m_drive->SplineDrive(
                        &second_left_scale_opposite_intaking::
                            second_left_scale_opposite_intaking,
                        Drive::RelativeTo::SetPoint);
                }
                else if (direction == AutoRoutineBase::AutoDirection::Right) {
                    m_drive->SplineDrive(
                        &second_right_scale_opposite_intaking::
                            second_right_scale_opposite_intaking,
                        Drive::RelativeTo::SetPoint);
                }
                m_autoTimer = GetMsecTime();
                m_autoState++;
            }
            break;
        case 4:
            if (m_intakeAssembly->IsCubeIn() ||
                GetMsecTime() - m_autoTimer > 3000) {
                if (direction == AutoRoutineBase::AutoDirection::Left) {
                    m_drive->SplineDrive(&second_left_scale_opposite_backoff::
                                             second_left_scale_opposite_backoff,
                                         Drive::RelativeTo::SetPoint);
                }
                else if (direction == AutoRoutineBase::AutoDirection::Right) {
                    m_drive->SplineDrive(
                        &second_right_scale_opposite_backoff::
                            second_right_scale_opposite_backoff,
                        Drive::RelativeTo::SetPoint);
                }
                m_intakeAssembly->GoToIntakePosition(
                    IntakeAssembly::OVER_BACK_PRESET);
                m_autoState++;
            }
            break;
        case 5:
            if (m_drive->GetSplinePercentComplete() > 0.8) {
                m_intakeAssembly->FastEjectCube();
                m_autoState++;
            }
            break;
        case 6:
            if (m_drive->OnTarget()) {
                m_intakeAssembly->GoToIntakePosition(
                    IntakeAssembly::GROUND_PRESET);
                m_intakeAssembly->OpenClaw();
                m_intakeAssembly->RunIntake(-1.0);
                if (direction == AutoRoutineBase::AutoDirection::Left) {
                    m_drive->SplineDrive(&third_left_scale_opposite_intaking::
                                             third_left_scale_opposite_intaking,
                                         Drive::RelativeTo::SetPoint);
                }
                else if (direction == AutoRoutineBase::AutoDirection::Right) {
                    m_drive->SplineDrive(
                        &third_right_scale_opposite_intaking::
                            third_right_scale_opposite_intaking,
                        Drive::RelativeTo::SetPoint);
                }
                m_autoTimer = GetMsecTime();
                m_autoState++;
            }
            break;
        case 7:
            if (m_intakeAssembly->IsCubeIn() ||
                GetMsecTime() - m_autoTimer > 3000) {
                if (direction == AutoRoutineBase::AutoDirection::Left) {
                    m_drive->SplineDrive(&third_left_scale_opposite_backoff::
                                             third_left_scale_opposite_backoff,
                                         Drive::RelativeTo::SetPoint);
                }
                else if (direction == AutoRoutineBase::AutoDirection::Right) {
                    m_drive->SplineDrive(&third_right_scale_opposite_backoff::
                                             third_right_scale_opposite_backoff,
                                         Drive::RelativeTo::SetPoint);
                }
                m_intakeAssembly->GoToIntakePosition(
                    IntakeAssembly::OVER_BACK_PRESET);
                m_autoState++;
            }
            break;
        case 8:
            if (m_drive->GetSplinePercentComplete() > 0.8) {
                m_intakeAssembly->FastEjectCube();
                m_autoState++;
            }
            break;
        case 9:
            if (m_drive->OnTarget()) {
                m_intakeAssembly->StopIntake();
                m_intakeAssembly->GoToIntakePosition(
                    IntakeAssembly::GROUND_PRESET);
                m_autoState++;
            }
            break;
        default:
            break;
    }
}

void ScaleOpposite::Reset() {
}
};
