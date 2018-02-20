#include "src/auto/SwitchAuto.h"
#include "src/auto/profiles/leftswitch_trajectory.h"

using namespace frc;
using namespace generated_profiles;

namespace frc973 {
SwitchAuto::SwitchAuto(Drive *drive, Elevator *elevator, Intake *intake,
                       Claw *claw)
        : m_drive(drive)
        , m_elevator(elevator)
        , m_intake(intake)
        , m_claw(claw)
        , m_autoState(0)
        , m_autoTimer(0) {
}

SwitchAuto::~SwitchAuto(void) {
}

void SwitchAuto::Execute(void) {
    std::cout << "No Auto" << std::endl;
    switch (m_autoState) {
        case 0:
            m_drive->SplineDrive(&generated_profiles::left_switch);
            m_elevator->SetPosition(Elevator::LOW_GOAL);
            m_autoTimer = GetMsecTime();
            m_autoState++;
            break;
        case 1:
            if (m_drive->OnTarget() || GetMsecTime() - m_autoTimer > 4000) {
                m_claw->cubeLaunch();
            }
        default:
            break;
    }
}

void SwitchAuto::Reset(void) {
}
};
