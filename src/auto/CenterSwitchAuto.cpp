#include "src/auto/CenterSwitchAuto.h"
#include "lib/util/WrapDash.h"
#include "src/auto/profiles/centerrightswitch_trajectory.h"
#include "src/auto/profiles/centerleftswitch_trajectory.h"
#include "src/auto/profiles/secondcenterrightswitchbackoff_trajectory.h"
#include "src/auto/profiles/secondcenterleftswitchbackoff_trajectory.h"
#include "src/auto/profiles/secondcenterrightswitchintaking_trajectory.h"
#include "src/auto/profiles/secondcenterleftswitchintaking_trajectory.h"
#include "src/auto/profiles/thirdcenterrightswitchbackoff_trajectory.h"
#include "src/auto/profiles/thirdcenterleftswitchbackoff_trajectory.h"
#include "src/auto/profiles/thirdcenterrightswitchintaking_trajectory.h"
#include "src/auto/profiles/thirdcenterleftswitchintaking_trajectory.h"
#include "src/auto/profiles/leftswitchreset_trajectory.h"
#include "src/auto/profiles/rightswitchreset_trajectory.h"

using namespace frc;
using namespace center_left_switch;
using namespace center_right_switch;
using namespace second_center_left_switch_backoff;
using namespace second_center_right_switch_backoff;
using namespace second_center_left_switch_intaking;
using namespace second_center_right_switch_intaking;
using namespace third_center_left_switch_backoff;
using namespace third_center_right_switch_backoff;
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

void CenterSwitchAuto::Execute(AutoRoutineBase::AutoDirection direction) {
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
                IntakeAssembly::OVER_BACK_PRESET);
            m_autoTimer = GetMsecTime();
            m_autoState++;
            break;
        case 1:
            if ((m_drive->GetSplinePercentComplete() > 0.80 &&
                 m_intakeAssembly->GetPositionError() < 10.0) ||
                GetMsecTime() - m_autoTimer > 4000) {
                m_intakeAssembly->EjectCube();
                m_autoState++;
            }
            break;
        case 2:
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
                m_intakeAssembly->GoToIntakePosition(
                    IntakeAssembly::GROUND_PRESET);
                m_intakeAssembly->RunIntake(-1.0);
                m_intakeAssembly->SoftCloseClaw();
                m_autoTimer = GetMsecTime();
                m_autoState++;
            }
            break;
        case 3:
            if (m_intakeAssembly->GetClaw()->IsCubeIn() ||
                GetMsecTime() - m_autoTimer > 3500) {
                m_intakeAssembly->HardCloseClaw();
                if (direction == AutoRoutineBase::AutoDirection::Left) {
                    m_drive->SplineDrive(&second_center_left_switch_backoff::
                                             second_center_left_switch_backoff,
                                         Drive::RelativeTo::Now);
                }
                else if (direction == AutoRoutineBase::AutoDirection::Right) {
                    m_drive->SplineDrive(&second_center_right_switch_backoff::
                                             second_center_right_switch_backoff,
                                         Drive::RelativeTo::Now);
                }
                m_autoTimer = GetMsecTime();
                m_autoState++;
            }
            break;
        case 4:
            if (GetMsecTime() - m_autoTimer > 500) {
                m_intakeAssembly->StopIntake();
                m_intakeAssembly->GoToIntakePosition(
                    IntakeAssembly::OVER_BACK_PRESET);
                m_autoTimer = GetMsecTime();
                m_autoState++;
            }
            break;
        case 5:
            if ((m_drive->GetSplinePercentComplete() > 0.80 &&
                 m_intakeAssembly->GetPositionError() < 10.0) ||
                GetMsecTime() - m_autoTimer > 4000) {
                m_intakeAssembly->FastEjectCube();
                m_autoState++;
            }
            break;
        case 6:
            if (m_drive->OnTarget()) {
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
                m_autoTimer = GetMsecTime();
                m_autoState++;
            }
            break;
        case 7:
            if (m_intakeAssembly->GetClaw()->IsCubeIn() ||
                GetMsecTime() - m_autoTimer > 3500) {
                m_intakeAssembly->HardCloseClaw();
                m_intakeAssembly->GoToIntakePosition(
                    IntakeAssembly::OVER_BACK_PRESET);
                if (direction == AutoRoutineBase::AutoDirection::Left) {
                    m_drive->SplineDrive(&third_center_left_switch_backoff::
                                             third_center_left_switch_backoff,
                                         Drive::RelativeTo::Now);
                }
                else if (direction == AutoRoutineBase::AutoDirection::Right) {
                    m_drive->SplineDrive(&third_center_right_switch_backoff::
                                             third_center_right_switch_backoff,
                                         Drive::RelativeTo::Now);
                }
                m_autoTimer = GetMsecTime();
                m_autoState++;
            }
            break;
        case 8:
            if (m_drive->GetSplinePercentComplete() > 0.8 &&
                m_intakeAssembly->GetPositionError() < 10.0) {
                m_intakeAssembly->FastEjectCube();
                m_autoState++;
            }
            break;
        case 9:
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
        case 10:
            if (m_drive->GetSplinePercentComplete() > 1.0 &&
                m_intakeAssembly->GetPositionError() < 10.0) {
                m_drive->OpenloopArcadeDrive(0.0, 0.0);
                m_intakeAssembly->GoToIntakePosition(
                    IntakeAssembly::GROUND_PRESET);
                m_autoState++;
            }
            break;
        default:
            break;
    }
    DBStringPrintf(DB_LINE7, "Done %.2lf", m_drive->GetSplinePercentComplete());
}

void CenterSwitchAuto::Reset(void) {
}
}
