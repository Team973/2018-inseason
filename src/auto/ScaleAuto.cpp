#include "src/auto/ScaleAuto.h"
#include "src/auto/profiles/rightscale_trajectory.h"
#include "src/auto/profiles/leftscale_trajectory.h"
#include "src/auto/profiles/secondleftscalebackoff_trajectory.h"
#include "src/auto/profiles/secondleftscaleintaking_trajectory.h"
#include "src/auto/profiles/secondrightscalebackoff_trajectory.h"
#include "src/auto/profiles/secondrightscaleintaking_trajectory.h"
#include "src/auto/profiles/thirdleftscalebackoff_trajectory.h"
#include "src/auto/profiles/thirdleftscaleintaking_trajectory.h"
#include "src/auto/profiles/thirdrightscalebackoff_trajectory.h"
#include "src/auto/profiles/thirdrightscaleintaking_trajectory.h"

using namespace frc;
using namespace left_scale;
using namespace right_scale;
using namespace second_left_scale_intaking;
using namespace second_left_scale_backoff;
using namespace second_right_scale_intaking;
using namespace second_right_scale_backoff;
using namespace third_left_scale_intaking;
using namespace third_left_scale_backoff;
using namespace third_right_scale_intaking;
using namespace third_right_scale_backoff;

namespace frc973 {
ScaleAuto::ScaleAuto(Drive *drive, IntakeAssembly *intakeAssembly)
        : m_drive(drive), m_intakeAssembly(intakeAssembly), m_autoTimer(0) {
}

ScaleAuto::~ScaleAuto() {
}

void ScaleAuto::Execute(AutoRoutineBase::AutoDirection direction) {
    std::cout << "Scale Auto" << std::endl;
    switch (m_autoState) {
        case 0:
            if (direction == AutoRoutineBase::AutoDirection::Left) {
                m_drive->SplineDrive(&left_scale::left_scale,
                                     Drive::RelativeTo::Now);
            }
            else if (direction == AutoRoutineBase::AutoDirection::Right) {
                m_drive->SplineDrive(&right_scale::right_scale,
                                     Drive::RelativeTo::Now);
            }
            m_autoTimer = GetMsecTime();
            m_autoState++;
            break;
        case 1:
            if (m_drive->GetSplinePercentComplete() > 0.6) {
                m_intakeAssembly->GoToIntakePosition(
                    IntakeAssembly::OVER_BACK_PRESET);
                m_autoTimer = GetMsecTime();
                m_autoState++;
            }
            break;
        case 2:
            if (m_drive->GetSplinePercentComplete() > 0.9 &&
                m_intakeAssembly->GetEndPositionError() < 10.0) {
                m_intakeAssembly->EjectCube();
                m_intakeAssembly->GoToIntakePosition(
                    IntakeAssembly::GROUND_PRESET);
                m_autoTimer = GetMsecTime();
                m_autoState++;
            }
            break;
        case 3:
            if (m_intakeAssembly->GetElevator()->GetPosition() < 30.0) {
                m_intakeAssembly->OpenClaw();
                m_intakeAssembly->RunIntake(-1.0);
                if (direction == AutoRoutineBase::AutoDirection::Left) {
                    m_drive->PIDDrive(0.0, 58.0, Drive::RelativeTo::Now, 1.0);
                    /*m_drive->SplineDrive(
                        &second_left_scale_intaking::second_left_scale_intaking,
                        Drive::RelativeTo::Now);*/
                }
                else if (direction == AutoRoutineBase::AutoDirection::Right) {
                    m_drive->PIDDrive(0.0, -55.0, Drive::RelativeTo::Now, 1.0);
                    /*
                                        m_drive->SplineDrive(&second_right_scale_intaking::
                                                                 second_right_scale_intaking,
                                                             Drive::RelativeTo::Now);*/
                }
                m_autoState++;
            }
            break;
        case 4:
            if (m_drive->OnTarget()) {
                if (direction == AutoRoutineBase::AutoDirection::Left) {
                    m_drive->PIDDrive(62.0, 0.0, Drive::RelativeTo::Now, 1.0);
                }
                else {
                    m_drive->PIDDrive(59.0, 0.0, Drive::RelativeTo::Now, 1.0);
                }
                m_autoTimer = GetMsecTime();
                m_autoState++;
            }
            break;
        case 5:
            if (m_drive->OnTarget() || GetMsecTime() - m_autoTimer > 2000) {
                m_intakeAssembly->SoftCloseClaw();
                if (direction == AutoRoutineBase::AutoDirection::Left) {
                    m_drive->SplineDrive(
                        &second_left_scale_backoff::second_left_scale_backoff,
                        Drive::RelativeTo::Now);
                }
                else if (direction == AutoRoutineBase::AutoDirection::Right) {
                    m_drive->SplineDrive(
                        &second_right_scale_backoff::second_right_scale_backoff,
                        Drive::RelativeTo::Now);
                }
                m_autoTimer = GetMsecTime();
                m_autoState++;
            }
            break;
        case 6:
            if (m_drive->GetSplinePercentComplete() > 0.2) {
                m_intakeAssembly->HoldCube();
                m_intakeAssembly->HardCloseClaw();
                m_intakeAssembly->GoToIntakePosition(
                    IntakeAssembly::HALF_STOW_PRESET);
                m_autoState++;
            }
            break;
        case 7:
            if (m_drive->GetSplinePercentComplete() > 0.5) {
                m_intakeAssembly->GoToIntakePosition(
                    IntakeAssembly::OVER_BACK_PRESET);
                m_autoState++;
            }
            break;
        case 8:
            if (m_intakeAssembly->GetWrist()->GetPosition() < -30.0) {
                m_intakeAssembly->EjectCube();
                m_intakeAssembly->GoToIntakePosition(
                    IntakeAssembly::GROUND_PRESET);
                m_autoState = -1;
            }
            break;
        case 9:
            m_autoState++;
            /*if (m_drive->GetSplinePercentComplete() > 0.4) {
                m_intakeAssembly->OpenClaw();
                m_intakeAssembly->RunIntake(-1.0);
            }
            if (m_drive->GetSplinePercentComplete() > 0.7) {
                m_intakeAssembly->SoftCloseClaw();
                m_autoState = -1;
            }
            if (m_intakeAssembly->GetClaw()->IsCubeIn() ||
                GetMsecTime() - m_autoTimer > 3500) {
                if (direction == AutoRoutineBase::AutoDirection::Left) {
                    m_drive->SplineDrive(
                        &third_left_scale_backoff::third_left_scale_backoff,
                        Drive::RelativeTo::Now);
                }
                else if (direction == AutoRoutineBase::AutoDirection::Right) {
                    m_drive->SplineDrive(
                        &third_right_scale_backoff::third_right_scale_backoff,
                        Drive::RelativeTo::Now);
                }
                m_intakeAssembly->HoldCube();
                m_intakeAssembly->HardCloseClaw();
                m_intakeAssembly->GoToIntakePosition(
                    IntakeAssembly::OVER_BACK_PRESET);
                m_autoState++;
            }*/
            break;
        case 10:
            if (m_drive->OnTarget()) {
                m_intakeAssembly->GoToIntakePosition(
                    IntakeAssembly::GROUND_PRESET);
                m_autoState++;
            }
            break;
        default:
            break;
    }
}

void ScaleAuto::Reset() {
}
};
