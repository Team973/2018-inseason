#include "src/auto/CenterSwitchAuto.h"
#include "lib/util/WrapDash.h"
#include "src/auto/profiles/centerrightswitch_trajectory.h"
#include "src/auto/profiles/centerleftswitch_trajectory.h"
#include "src/auto/profiles/centerrightswitchbackoff_trajectory.h"
#include "src/auto/profiles/centerleftswitchbackoff_trajectory.h"
#include "src/auto/profiles/leftswitchreset_trajectory.h"
#include "src/auto/profiles/rightswitchreset_trajectory.h"

using namespace frc;
using namespace center_left_switch;
using namespace center_right_switch;
using namespace center_left_switch_backoff;
using namespace center_right_switch_backoff;
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
                IntakeAssembly::LOW_GOAL_PRESET);
            m_autoTimer = GetMsecTime();
            m_autoState++;
            break;
        case 1:
            if (m_drive->GetSplinePercentComplete() > 0.80 ||
                m_drive->OnTarget() || GetMsecTime() - m_autoTimer > 4000) {
                m_intakeAssembly->EjectCube();
                m_autoState++;
            }
            break;
        case 2:
            if (m_drive->GetSplinePercentComplete() > 0.9) {
                if (direction == AutoRoutineBase::AutoDirection::Left) {
                    m_drive->SplineDrive(
                        &center_left_switch_backoff::center_left_switch_backoff,
                        Drive::RelativeTo::SetPoint);
                }
                else if (direction == AutoRoutineBase::AutoDirection::Right) {
                    m_drive->SplineDrive(&center_right_switch_backoff::
                                             center_right_switch_backoff,
                                         Drive::RelativeTo::SetPoint);
                }
                m_intakeAssembly->GoToIntakePosition(
                    IntakeAssembly::GROUND_PRESET);
                m_autoState++;
            }
            break;
        case 3:
            if (m_drive->GetSplinePercentComplete() > 0.9) {
                m_intakeAssembly->IntakeCube(-1.0);
                m_intakeAssembly->DropCube();
                if (direction == AutoRoutineBase::AutoDirection::Left) {
                    m_drive->PIDDrive(44.0, -5.0, Drive::RelativeTo::Now, 1.0);
                }
                else {
                    m_drive->PIDDrive(44.0, 5.0, Drive::RelativeTo::Now, 1.0);
                }
                m_autoTimer = GetMsecTime();
                m_autoState++;
            }
            break;
        case 4:
            if (m_drive->GetPIDDistError() < 5.0) {
                m_intakeAssembly->GrabCube();
            }
            if (m_intakeAssembly->GetWrist()->IsCubeIn() ||
                GetMsecTime() - m_autoTimer > 3500) {
                m_intakeAssembly->GrabCube();
                m_autoTimer = GetMsecTime();
                m_autoState++;
            }
            break;
        case 5:
            if (GetMsecTime() - m_autoTimer > 500) {
                m_intakeAssembly->StopIntake();
                m_drive->PIDDrive(-63.0, 0.0, Drive::RelativeTo::SetPoint, 1.0);
                m_autoTimer = GetMsecTime();
                m_autoState++;
            }
            break;
        case 6:
            if (m_drive->OnTarget() || GetMsecTime() - m_autoTimer > 2000) {
                if (direction == AutoRoutineBase::AutoDirection::Left) {
                    m_drive->SplineDrive(
                        &center_left_switch::center_left_switch,
                        Drive::RelativeTo::Now);
                }
                else if (direction == AutoRoutineBase::AutoDirection::Right) {
                    m_drive->SplineDrive(
                        &center_right_switch::center_right_switch,
                        Drive::RelativeTo::Now);
                }
                m_intakeAssembly->GoToIntakePosition(
                    IntakeAssembly::LOW_GOAL_PRESET);
                m_autoTimer = GetMsecTime();
                m_autoState++;
            }
            break;
        case 7:
            if (m_drive->GetSplinePercentComplete() > 0.8) {
                m_intakeAssembly->EjectCube();
                m_autoState++;
            }
            break;
        case 8:
            if (m_drive->GetSplinePercentComplete() > 0.85) {
                if (direction == AutoRoutineBase::AutoDirection::Left) {
                    m_drive->SplineDrive(&left_switch_reset::left_switch_reset,
                                         Drive::RelativeTo::SetPoint);
                }
                else if (direction == AutoRoutineBase::AutoDirection::Right) {
                    m_drive->SplineDrive(
                        &right_switch_reset::right_switch_reset,
                        Drive::RelativeTo::SetPoint);
                }
                m_intakeAssembly->GoToIntakePosition(
                    IntakeAssembly::GROUND_PRESET);
                m_intakeAssembly->StopIntake();
                m_autoState++;
            }
            break;
        case 9:
            if (m_drive->GetSplinePercentComplete() > 1.0) {
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
