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
SwitchOpposite::SwitchOpposite(Drive *drive, IntakeAssembly *intakeAssembly)
        : m_drive(drive), m_intakeAssembly(intakeAssembly), m_autoTimer(0) {
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
            m_intakeAssembly->GoToIntakePosition(
                IntakeAssembly::LOW_GOAL_PRESET);
            m_autoState++;
            break;
        case 1:
            if (m_drive->GetSplinePercentComplete() > 1.0 ||
                m_drive->OnTarget()) {
                m_intakeAssembly->EjectCube();
                m_autoState++;
            }
            break;
        case 2:
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
        case 3:
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
}
void SwitchOpposite::Reset(void) {
}
};
