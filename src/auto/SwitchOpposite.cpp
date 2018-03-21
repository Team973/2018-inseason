#include "src/auto/SwitchOpposite.h"
#include "src/auto/profiles/rightswitchopposite_trajectory.h"
#include "src/auto/profiles/leftswitchopposite_trajectory.h"
#include "src/auto/profiles/leftswitchreset_trajectory.h"
#include "src/auto/profiles/rightswitchreset_trajectory.h"

using namespace frc;
using namespace left_switch_opposite;
using namespace right_switch_opposite;
using namespace right_switch_reset;
using namespace left_switch_reset;

namespace frc973 {
SwitchOpposite::SwitchOpposite(Drive *drive, Elevator *elevator, Claw *claw)
        : m_drive(drive), m_elevator(elevator), m_claw(claw), m_autoTimer(0) {
}

SwitchOpposite::~SwitchOpposite(void) {
}

void SwitchOpposite::Execute(AutoRoutineBase::AutoDirection direction) {
    std::cout << "Scale Auto" << std::endl;
    switch (m_autoState) {
        case 0:
            if (direction == AutoRoutineBase::AutoDirection::Left) {
                m_drive->SplineDrive(
                    &right_switch_opposite::right_switch_opposite,
                    Drive::RelativeTo::Now);
            }
            else if (direction == AutoRoutineBase::AutoDirection::Right) {
                m_drive->SplineDrive(
                    &left_switch_opposite::left_switch_opposite,
                    Drive::RelativeTo::Now);
            }
            m_elevator->SetPosition(Elevator::LOW_GOAL);
            m_claw->grab();
            m_claw->kickOff();
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
            if (m_drive->GetSplinePercentComplete() > 0.8 ||
                m_drive->OnTarget() || GetMsecTime() - m_autoTimer > 5000) {
                m_claw->cubeLaunch();
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
}
void SwitchOpposite::Reset(void) {
}
};
