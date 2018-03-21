#include "src/auto/CenterSwitchAuto.h"
#include "lib/util/WrapDash.h"
#include "src/auto/profiles/centerrightswitch_trajectory.h"
#include "src/auto/profiles/centerleftswitch_trajectory.h"
#include "src/auto/profiles/leftswitchreset_trajectory.h"
#include "src/auto/profiles/rightswitchreset_trajectory.h"

using namespace frc;
using namespace center_left_switch;
using namespace center_right_switch;
using namespace right_switch_reset;
using namespace left_switch_reset;

namespace frc973 {
CenterSwitchAuto::CenterSwitchAuto(Drive *drive, Elevator *elevator, Claw *claw)
        : m_drive(drive), m_elevator(elevator), m_claw(claw), m_autoTimer(0) {
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
            m_elevator->SetPosition(Elevator::LOW_GOAL);
            m_claw->CloseClaw();
            m_autoTimer = GetMsecTime();
            m_autoState++;
            break;
        case 1:
            if (GetMsecTime() - m_autoTimer > 2000) {
                m_autoTimer = GetMsecTime();
                m_autoState++;
            }
            break;
        case 2:
            if (m_drive->GetSplinePercentComplete() > 0.80 ||
                m_drive->OnTarget() || GetMsecTime() - m_autoTimer > 4000) {
                m_autoState++;
            }
            break;
        case 3:
            if (m_drive->GetSplinePercentComplete() > 1.0) {
                if (direction == AutoRoutineBase::AutoDirection::Left) {
                    m_drive->SplineDrive(&left_switch_reset::left_switch_reset,
                                         Drive::RelativeTo::SetPoint);
                }
                else if (direction == AutoRoutineBase::AutoDirection::Right) {
                    m_drive->SplineDrive(
                        &right_switch_reset::right_switch_reset,
                        Drive::RelativeTo::SetPoint);
                }
                m_autoState++;
            }
            break;
        case 4:
            if (m_drive->GetSplinePercentComplete() > 1.0) {
                m_drive->OpenloopArcadeDrive(0.0, 0.0);
                m_elevator->SetPosition(Elevator::GROUND);
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
