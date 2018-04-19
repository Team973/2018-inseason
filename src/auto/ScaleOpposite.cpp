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
    std::cout << "Scale Auto" << std::endl;
    switch (m_autoState) {
        case 0:
            m_drive->PIDDrive(-228.0, 0.0, Drive::RelativeTo::Now, 0.9)
                ->SetVMax(180.0, 360.0);
            /*if (direction == AutoRoutineBase::AutoDirection::Right) {
                m_drive->SplineDrive(&left_scale_opposite::left_scale_opposite,
                                     Drive::RelativeTo::Now);
            }
            else if (direction == AutoRoutineBase::AutoDirection::Left) {
                m_drive->SplineDrive(
                    &right_scale_opposite::right_scale_opposite,
                    Drive::RelativeTo::Now);
            }*/
            m_autoTimer = GetMsecTime();
            m_autoState++;
            break;
        case 1:
            if (m_drive->OnTarget()) {
                if (direction == AutoRoutineBase::AutoDirection::Right) {
                    m_drive
                        ->PIDDrive(0.0, -90.0, Drive::RelativeTo::SetPoint, 0.8)
                        ->SetVMax(120.0, 330.0);
                }
                else if (direction == AutoRoutineBase::AutoDirection::Left) {
                    m_drive
                        ->PIDDrive(0.0, 90.0, Drive::RelativeTo::SetPoint, 0.8)
                        ->SetVMax(120.0, 330.0);
                }
                m_autoState++;
            }
            break;
        case 2:
            if (m_drive->OnTarget()) {
                if (direction == AutoRoutineBase::AutoDirection::Right) {
                    m_drive
                        ->PIDDrive(-228.0, 0.0, Drive::RelativeTo::SetPoint,
                                   0.9)
                        ->SetVMax(150.0, 360.0);
                }
                else if (direction == AutoRoutineBase::AutoDirection::Left) {
                    m_drive
                        ->PIDDrive(-218.0, 0.0, Drive::RelativeTo::SetPoint,
                                   0.9)
                        ->SetVMax(150.0, 360.0);
                }
                m_autoState++;
            }
            break;
        case 3:
            if (m_drive->OnTarget()) {
                if (direction == AutoRoutineBase::AutoDirection::Right) {
                    m_drive
                        ->PIDDrive(0.0, 100.0, Drive::RelativeTo::SetPoint, 0.8)
                        ->SetVMax(120.0, 330.0);
                }
                else if (direction == AutoRoutineBase::AutoDirection::Left) {
                    m_drive
                        ->PIDDrive(0.0, -100.0, Drive::RelativeTo::SetPoint,
                                   0.8)
                        ->SetVMax(120.0, 330.0);
                }
                m_autoState++;
            }
            break;
        case 4:
            if (m_drive->GetPIDDistError() < 10.0) {
                m_intakeAssembly->GoToIntakePosition(
                    IntakeAssembly::OVER_BACK_PRESET);
            }
            if (m_drive->OnTarget()) {
                if (direction == AutoRoutineBase::AutoDirection::Right) {
                    m_drive
                        ->PIDDrive(-52.0, 0.0, Drive::RelativeTo::SetPoint, 0.9)
                        ->SetVMax(120.0, 360.0);
                }
                else if (direction == AutoRoutineBase::AutoDirection::Left) {
                    m_drive
                        ->PIDDrive(-58.0, 0.0, Drive::RelativeTo::SetPoint, 0.9)
                        ->SetVMax(100.0, 360.0);
                }
                m_autoState++;
            }
            break;
        case 5:
            if (m_drive->GetPIDDistError() < 10.0 &&
                m_intakeAssembly->GetPositionError() < 25.0) {
                m_intakeAssembly->RunIntake(1.0);
            }
            if (m_drive->OnTarget() &&
                m_intakeAssembly->GetPositionError() < 10.0) {
                m_intakeAssembly->RunIntake(1.0);
                m_intakeAssembly->GoToIntakePosition(
                    IntakeAssembly::GROUND_PRESET);
                m_autoTimer = GetMsecTime();
                m_autoState++;
            }
            break;
        case 6:
            if (m_intakeAssembly->GetElevator()->GetPosition() < 30.0 ||
                GetMsecTime() - m_autoTimer > 1000) {
                m_intakeAssembly->OpenClaw();
                m_intakeAssembly->RunIntake(-1.0);
                if (direction == AutoRoutineBase::AutoDirection::Left) {
                    m_drive->PIDDrive(0.0, 22.0, Drive::RelativeTo::Now, 1.0)
                        ->SetVMax(120.0, 360.0);
                    /*m_drive->SplineDrive(
                        &second_left_scale_intaking::second_left_scale_intaking,
                        Drive::RelativeTo::Now);*/
                }
                else if (direction == AutoRoutineBase::AutoDirection::Right) {
                    m_drive->PIDDrive(0.0, -20.0, Drive::RelativeTo::Now, 1.0)
                        ->SetVMax(120.0, 360.0);
                    /*
                                        m_drive->SplineDrive(&second_right_scale_intaking::
                                                                 second_right_scale_intaking,
                                                             Drive::RelativeTo::Now);*/
                }
                /*if (GetMsecTime() - m_autoTimer > 1000) {
                    if (direction == AutoRoutineBase::AutoDirection::Right) {
                        m_drive->SplineDrive(
                            &second_left_scale_opposite_intaking::
                                second_left_scale_opposite_intaking,
                            Drive::RelativeTo::Now);
                    }
                    else if (direction == AutoRoutineBase::AutoDirection::Left)
                { m_drive->SplineDrive( &second_right_scale_opposite_intaking::
                                second_right_scale_opposite_intaking,
                            Drive::RelativeTo::Now);
                    }
                    m_autoState++;
                }*/
                m_autoState++;
            }
            break;
        case 7:
            if (m_drive->OnTarget()) {
                if (direction == AutoRoutineBase::AutoDirection::Left) {
                    m_drive->PIDDrive(61.0, 0.0, Drive::RelativeTo::Now, 1.0)
                        ->SetVMax(120.0, 360.0);
                }
                else if (direction == AutoRoutineBase::AutoDirection::Right) {
                    m_drive->PIDDrive(62.0, 0.0, Drive::RelativeTo::Now, 1.0)
                        ->SetVMax(120.0, 360.0);
                }
                m_autoTimer = GetMsecTime();
                m_autoState++;
            }
            break;
        case 8:
            if (m_drive->OnTarget() || GetMsecTime() - m_autoTimer > 2000) {
                m_intakeAssembly->SoftCloseClaw();
                if (direction == AutoRoutineBase::AutoDirection::Right) {
                    m_drive->SplineDrive(&second_left_scale_opposite_backoff::
                                             second_left_scale_opposite_backoff,
                                         Drive::RelativeTo::Now);
                }
                else if (direction == AutoRoutineBase::AutoDirection::Left) {
                    m_drive->SplineDrive(
                        &second_right_scale_opposite_backoff::
                            second_right_scale_opposite_backoff,
                        Drive::RelativeTo::Now);
                }
                m_autoTimer = GetMsecTime();
                m_autoState++;
            }
            break;
        case 9:
            if (m_drive->GetSplinePercentComplete() > 0.1) {
                m_intakeAssembly->GoToIntakePosition(
                    IntakeAssembly::OVER_BACK_PRESET);
                m_intakeAssembly->HardCloseClaw();
                m_intakeAssembly->HoldCube();
                m_autoState++;
            }
            break;
        case 10:
            if (m_drive->GetSplinePercentComplete() > 0.9 &&
                m_intakeAssembly->GetPositionError() < 10.0) {
                m_intakeAssembly->EjectCube();
                m_autoTimer = GetMsecTime();
                m_autoState = -1;
            }
            break;
        case 12:
            /*if (m_intakeAssembly->GetClaw()->IsCubeIn() ||
                GetMsecTime() - m_autoTimer > 3000) {
                if (direction == AutoRoutineBase::AutoDirection::Right) {
                    m_drive->SplineDrive(&second_left_scale_opposite_backoff::
                                             second_left_scale_opposite_backoff,
                                         Drive::RelativeTo::Now);
                }
                else if (direction == AutoRoutineBase::AutoDirection::Left) {
                    m_drive->SplineDrive(
                        &second_right_scale_opposite_backoff::
                            second_right_scale_opposite_backoff,
                        Drive::RelativeTo::Now);
                }
                m_intakeAssembly->HardCloseClaw();
                m_intakeAssembly->GoToIntakePosition(
                    IntakeAssembly::OVER_BACK_PRESET);
                m_autoState++;
            }*/
            break;
        case 13:
            if (m_drive->GetSplinePercentComplete() > 0.8 &&
                m_intakeAssembly->GetPositionError() < 10.0) {
                m_intakeAssembly->FastEjectCube();
                m_autoTimer = GetMsecTime();
                m_autoState++;
            }
            break;
        case 14:
            if (m_drive->OnTarget() && GetMsecTime() - m_autoTimer > 1000) {
                m_intakeAssembly->GoToIntakePosition(
                    IntakeAssembly::GROUND_PRESET);
                m_intakeAssembly->SoftCloseClaw();
                m_intakeAssembly->RunIntake(-1.0);
                if (direction == AutoRoutineBase::AutoDirection::Right) {
                    m_drive->SplineDrive(&third_left_scale_opposite_intaking::
                                             third_left_scale_opposite_intaking,
                                         Drive::RelativeTo::Now);
                }
                else if (direction == AutoRoutineBase::AutoDirection::Left) {
                    m_drive->SplineDrive(
                        &third_right_scale_opposite_intaking::
                            third_right_scale_opposite_intaking,
                        Drive::RelativeTo::Now);
                }
                m_autoTimer = GetMsecTime();
                m_autoState++;
            }
            break;
        case 15:
            if (m_intakeAssembly->GetClaw()->IsCubeIn() ||
                GetMsecTime() - m_autoTimer > 3000) {
                if (direction == AutoRoutineBase::AutoDirection::Right) {
                    m_drive->SplineDrive(&third_left_scale_opposite_backoff::
                                             third_left_scale_opposite_backoff,
                                         Drive::RelativeTo::Now);
                }
                else if (direction == AutoRoutineBase::AutoDirection::Left) {
                    m_drive->SplineDrive(&third_right_scale_opposite_backoff::
                                             third_right_scale_opposite_backoff,
                                         Drive::RelativeTo::Now);
                }
                m_intakeAssembly->GoToIntakePosition(
                    IntakeAssembly::OVER_BACK_PRESET);
                m_intakeAssembly->HardCloseClaw();
                m_autoState++;
            }
            break;
        case 16:
            if (m_drive->GetSplinePercentComplete() > 0.8 &&
                m_intakeAssembly->GetPositionError() < 10.0) {
                m_intakeAssembly->FastEjectCube();
                m_autoTimer = GetMsecTime();
                m_autoState++;
            }
            break;
        case 17:
            if ((m_drive->OnTarget() &&
                 m_intakeAssembly->GetPositionError() < 10.0) &&
                GetMsecTime() - m_autoTimer > 1300) {
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
