#include "src/auto/CenterSwitchAuto.h"
#include "lib/util/WrapDash.h"
#include "src/auto/profiles/centerrightswitch_trajectory.h"
#include "src/auto/profiles/centerleftswitch_trajectory.h"
#include "src/auto/profiles/secondcenterrightswitchscoring_trajectory.h"
#include "src/auto/profiles/secondcenterleftswitchscoring_trajectory.h"
#include "src/auto/profiles/secondcenterrightswitchintaking_trajectory.h"
#include "src/auto/profiles/secondcenterleftswitchintaking_trajectory.h"
#include "src/auto/profiles/thirdcenterrightswitchscoring_trajectory.h"
#include "src/auto/profiles/thirdcenterleftswitchscoring_trajectory.h"
#include "src/auto/profiles/thirdcenterrightswitchintaking_trajectory.h"
#include "src/auto/profiles/thirdcenterleftswitchintaking_trajectory.h"
#include "src/auto/profiles/leftswitchreset_trajectory.h"
#include "src/auto/profiles/rightswitchreset_trajectory.h"

using namespace frc;
using namespace center_left_switch;
using namespace center_right_switch;
using namespace second_center_left_switch_scoring;
using namespace second_center_right_switch_scoring;
using namespace second_center_left_switch_intaking;
using namespace second_center_right_switch_intaking;
using namespace third_center_left_switch_scoring;
using namespace third_center_right_switch_scoring;
using namespace third_center_left_switch_intaking;
using namespace third_center_right_switch_intaking;
using namespace right_switch_reset;
using namespace left_switch_reset;

namespace frc973 {
CenterSwitchAuto::CenterSwitchAuto(Drive *drive, IntakeAssembly *intakeAssembly)
        : m_drive(drive), m_intakeAssembly(intakeAssembly), m_autoTimer(0) {
}

CenterSwitchAuto::~CenterSwitchAuto(void) {
}

void CenterSwitchAuto::Execute(AutoRoutineBase::AutoDirection direction,
                               std::string scalePos) {
    switch (m_autoState) {
        case 0:
            if (direction == AutoRoutineBase::AutoDirection::Left) {
                m_drive->SplineDrive(&center_left_switch::center_left_switch,
                                     Drive::RelativeTo::Now);
            }
            else if (direction == AutoRoutineBase::AutoDirection::Right) {
                m_drive->SplineDrive(&center_right_switch::center_right_switch,
                                     Drive::RelativeTo::Now);
            }
            m_intakeAssembly->GoToIntakePosition(
                IntakeAssembly::LOW_GOAL_PRESET);
            m_autoTimer = GetMsecTime();
            m_autoState++;
            break;
        case 1:
            if ((m_drive->GetSplinePercentComplete() > 0.75 &&
                 m_intakeAssembly->GetPositionError() < 10.0) ||
                GetMsecTime() - m_autoTimer > 4000) {
                m_intakeAssembly->EjectCube();
                m_autoState++;
            }
            break;
        case 2:
            if (m_drive->GetSplinePercentComplete() > 0.85) {
                if (direction == AutoRoutineBase::AutoDirection::Left) {
                    m_drive->SplineDrive(&second_center_left_switch_intaking::
                                             second_center_left_switch_intaking,
                                         Drive::RelativeTo::Now);
                }
                else if (direction == AutoRoutineBase::AutoDirection::Right) {
                    m_drive->SplineDrive(
                        &second_center_right_switch_intaking::
                            second_center_right_switch_intaking,
                        Drive::RelativeTo::Now);
                }
                m_intakeAssembly->OpenClaw();
                m_autoState++;
            }
            break;
        case 3:
            if (m_drive->GetSplinePercentComplete() > 0.5) {
                m_intakeAssembly->RunIntake(-1.0);
                m_intakeAssembly->GoToIntakePosition(
                    IntakeAssembly::GROUND_PRESET);
            }
            if (m_drive->OnTarget()) {
                if (direction == AutoRoutineBase::AutoDirection::Left) {
                    m_drive->PIDDrive(40.0, -m_drive->GetAngle(),
                                      Drive::RelativeTo::Now, 1.0);
                }
                else {
                    m_drive->PIDDrive(40.0, -m_drive->GetAngle(),
                                      Drive::RelativeTo::Now, 1.0);
                }
                m_autoTimer = GetMsecTime();
                m_autoState++;
            }
            break;
        case 4:
            if (m_drive->OnTarget() || GetMsecTime() - m_autoTimer > 2500) {
                m_intakeAssembly->HardCloseClaw();
                m_autoTimer = GetMsecTime();
                m_autoState++;
            }
            break;
        case 5:
            if (GetMsecTime() - m_autoTimer > 250) {
                m_drive->PIDDrive(-60.0, 0.0, Drive::RelativeTo::Now, 1.0);
                m_intakeAssembly->GoToIntakePosition(
                    IntakeAssembly::HALF_STOW_PRESET);
                m_autoTimer = GetMsecTime();
                m_autoState++;
            }
            break;
        case 6:
            if (m_drive->OnTarget() || GetMsecTime() - m_autoTimer > 1500) {
                if (direction == AutoRoutineBase::AutoDirection::Left) {
                    m_drive->SplineDrive(&second_center_left_switch_scoring::
                                             second_center_left_switch_scoring,
                                         Drive::RelativeTo::Now);
                }
                else if (direction == AutoRoutineBase::AutoDirection::Right) {
                    m_drive->SplineDrive(&second_center_right_switch_scoring::
                                             second_center_right_switch_scoring,
                                         Drive::RelativeTo::Now);
                }
                m_intakeAssembly->GoToIntakePosition(
                    IntakeAssembly::LOW_GOAL_PRESET);
                m_intakeAssembly->HoldCube();
                m_autoTimer = GetMsecTime();
                m_autoState++;
            }
            break;
        case 7:
            if (m_drive->GetSplinePercentComplete() > 0.8) {
                m_intakeAssembly->FastEjectCube();
                m_autoTimer = GetMsecTime();
                m_autoState++;
            }
            break;
        case 8:
            if (m_drive->GetSplinePercentComplete() > 0.9) {
                if (direction == AutoRoutineBase::AutoDirection::Left) {
                    m_drive->SplineDrive(&second_center_left_switch_intaking::
                                             second_center_left_switch_intaking,
                                         Drive::RelativeTo::Now);
                }
                else if (direction == AutoRoutineBase::AutoDirection::Right) {
                    m_drive->SplineDrive(
                        &second_center_right_switch_intaking::
                            second_center_right_switch_intaking,
                        Drive::RelativeTo::Now);
                }
                m_intakeAssembly->OpenClaw();
                m_autoState++;
            }
            break;
        case 9:
            if (m_drive->GetSplinePercentComplete() > 0.5) {
                m_intakeAssembly->RunIntake(-1.0);
                m_intakeAssembly->GoToIntakePosition(
                    IntakeAssembly::SECOND_STACK_PRESET);
            }
            if (m_drive->OnTarget()) {
                m_drive->PIDDrive(47.0, -m_drive->GetAngle(),
                                  Drive::RelativeTo::Now, 1.0);
                m_autoState++;
            }
            break;
        case 10:
            if (m_drive->OnTarget()) {
                m_intakeAssembly->HardCloseClaw();
                m_autoTimer = GetMsecTime();
                m_autoState++;
            }
            break;
        case 11:
            if (GetMsecTime() - m_autoTimer > 250) {
                if (scalePos == "L") {
                    m_drive->SplineDrive(&left_switch_reset::left_switch_reset,
                                         Drive::RelativeTo::Now);
                }
                else {
                    m_drive->SplineDrive(
                        &right_switch_reset::right_switch_reset,
                        Drive::RelativeTo::Now);
                }
                m_intakeAssembly->GoToIntakePosition(
                    IntakeAssembly::HALF_STOW_PRESET);
                m_autoState++;
            }
            break;
        case 12:
            if (m_drive->OnTarget()) {
                if (direction == AutoRoutineBase::AutoDirection::Left) {
                    m_drive->SplineDrive(&second_center_left_switch_scoring::
                                             second_center_left_switch_scoring,
                                         Drive::RelativeTo::Now);
                }
                else if (direction == AutoRoutineBase::AutoDirection::Right) {
                    m_drive->SplineDrive(&second_center_right_switch_scoring::
                                             second_center_right_switch_scoring,
                                         Drive::RelativeTo::Now);
                }
                m_intakeAssembly->GoToIntakePosition(
                    IntakeAssembly::LOW_GOAL_PRESET);
                m_intakeAssembly->HoldCube();
                m_autoTimer = GetMsecTime();
                m_autoState++;
            }
            break;
        case 13:
            if (m_drive->GetSplinePercentComplete() > 0.8) {
                m_intakeAssembly->FastEjectCube();
                m_autoTimer = GetMsecTime();
                m_autoState++;
            }
            break;
            /*if (m_drive->OnTarget()) {
                if (direction == AutoRoutineBase::AutoDirection::Left) {
                    m_drive->SplineDrive(&third_center_left_switch_intaking::
                                             third_center_left_switch_intaking,
                                         Drive::RelativeTo::Now);
                }
                else if (direction == AutoRoutineBase::AutoDirection::Right) {
                    m_drive->SplineDrive(&third_center_right_switch_intaking::
                                             third_center_right_switch_intaking,
                                         Drive::RelativeTo::Now);
                }
                m_intakeAssembly->GoToIntakePosition(
                    IntakeAssembly::SECOND_STACK_PRESET);
                m_intakeAssembly->RunIntake(-1.0);
                m_intakeAssembly->SoftCloseClaw();
                m_autoState++;
            }
            break;
        case 9:
            if (m_drive->OnTarget()) {
                m_drive->PIDDrive(70.0, 0.0, Drive::RelativeTo::Now, 1.0);
                m_autoTimer = GetMsecTime();
                m_autoState++;
            }
            break;
        case 10:
            if ((m_intakeAssembly->GetClaw()->IsCubeIn() &&
                 m_drive->OnTarget()) ||
                GetMsecTime() - m_autoTimer > 3500) {
                m_intakeAssembly->HardCloseClaw();
                m_drive->PIDDrive(-70.0, 0.0, Drive::RelativeTo::Now, 1.0);
                m_autoTimer = GetMsecTime();
                m_autoState++;
            }
            break;
        case 11:
            if (m_drive->OnTarget() || GetMsecTime() - m_autoTimer > 3500) {
                m_intakeAssembly->HardCloseClaw();
                m_intakeAssembly->GoToIntakePosition(
                    IntakeAssembly::LOW_GOAL_PRESET);
                if (direction == AutoRoutineBase::AutoDirection::Left) {
                    m_drive->SplineDrive(&third_center_left_switch_scoring::
                                             third_center_left_switch_scoring,
                                         Drive::RelativeTo::Now);
                }
                else if (direction == AutoRoutineBase::AutoDirection::Right) {
                    m_drive->SplineDrive(&third_center_right_switch_scoring::
                                             third_center_right_switch_scoring,
                                         Drive::RelativeTo::Now);
                }
                m_autoTimer = GetMsecTime();
                m_autoState++;
            }
            break;
        case 12:
            if ((m_drive->GetSplinePercentComplete() > 0.80 &&
                 m_intakeAssembly->GetPositionError() < 10.0) ||
                GetMsecTime() - m_autoTimer > 4000) {
                m_intakeAssembly->FastEjectCube();
                m_autoState++;
            }
            break;
        case 13:
            if (m_drive->GetSplinePercentComplete() > 0.9) {
                if (direction == AutoRoutineBase::AutoDirection::Left) {
                    m_drive->SplineDrive(&left_switch_reset::left_switch_reset,
                                         Drive::RelativeTo::Now);
                }
                else if (direction == AutoRoutineBase::AutoDirection::Right) {
                    m_drive->SplineDrive(
                        &right_switch_reset::right_switch_reset,
                        Drive::RelativeTo::Now);
                }
                m_intakeAssembly->GoToIntakePosition(
                    IntakeAssembly::GROUND_PRESET);
                m_intakeAssembly->StopIntake();
                m_autoState++;
            }
            break;
        case 14:
            if (m_drive->GetSplinePercentComplete() > 1.0 &&
                m_intakeAssembly->GetPositionError() < 10.0) {
                m_drive->OpenloopArcadeDrive(0.0, 0.0);
                m_intakeAssembly->GoToIntakePosition(
                    IntakeAssembly::GROUND_PRESET);
                m_autoState++;
            }
            break;*/
        default:
            break;
    }
    DBStringPrintf(DB_LINE7, "Done %.2lf", m_drive->GetSplinePercentComplete());
}

void CenterSwitchAuto::Reset(void) {
}
}
