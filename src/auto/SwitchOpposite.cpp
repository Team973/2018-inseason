#include "src/auto/SwitchOpposite.h"
#include "src/auto/profiles/rightswitchopposite_trajectory.h"
#include "src/auto/profiles/leftswitchopposite_trajectory.h"

using namespace frc;
using namespace left_switch_opposite;
using namespace right_switch_opposite;

namespace frc973 {
SwitchOpposite::SwitchOpposite(Drive *drive, Elevator *elevator, Intake *intake,
                               Claw *claw)
        : m_drive(drive)
        , m_elevator(elevator)
        , m_intake(intake)
        , m_claw(claw)
        , m_autoTimer(0) {
}

SwitchOpposite::~SwitchOpposite(void) {
}

void SwitchOpposite::Execute(AutoRoutineBase::AutoDirection direction) {
    std::cout << "Scale Auto" << std::endl;
    switch (m_autoState) {
        case 0:
            if (direction == AutoRoutineBase::AutoDirection::Left) {
                m_drive->SplineDrive(
                    &left_switch_opposite::left_switch_opposite);
            }
            else if (direction == AutoRoutineBase::AutoDirection::Left) {
                m_drive->SplineDrive(
                    &right_switch_opposite::right_switch_opposite);
            }
            m_intake->Open();
            m_intake->LowerIntake();
            m_claw->grab();
            m_claw->kickOff();
            m_autoTimer = GetMsecTime();
            m_autoState++;
            break;
        case 1:
            if (GetMsecTime() - m_autoTimer > 1000) {
                m_elevator->SetPosition(Elevator::LOW_GOAL);
                m_autoTimer = GetMsecTime();
                m_autoState++;
            }
            break;
        case 2:
            if (m_drive->OnTarget() || GetMsecTime() - m_autoTimer > 5000) {
                m_claw->cubeLaunch();
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
