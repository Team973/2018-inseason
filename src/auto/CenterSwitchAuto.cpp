#include "src/auto/CenterSwitchAuto.h"
#include "src/auto/profiles/centerrightswitch_trajectory.h"
#include "src/auto/profiles/centerleftswitch_trajectory.h"

using namespace frc;
using namespace center_left_switch;
using namespace center_right_switch;

namespace frc973 {
CenterSwitchAuto::CenterSwitchAuto(Drive *drive, Elevator *elevator,
                                   Intake *intake, Claw *claw)
        : m_drive(drive)
        , m_elevator(elevator)
        , m_intake(intake)
        , m_claw(claw)
        , m_autoTimer(0) {
}

CenterSwitchAuto::~CenterSwitchAuto(void) {
}

void CenterSwitchAuto::Execute(AutoRoutineBase::AutoDirection direction) {
    switch (m_autoState) {
        case 0:
            if (direction == AutoRoutineBase::AutoDirection::Left) {
                m_drive->SplineDrive(&center_left_switch::center_left_switch);
            }
            else if (direction == AutoRoutineBase::AutoDirection::Right) {
                m_drive->SplineDrive(&center_right_switch::center_right_switch);
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
            if (m_drive->OnTarget() || GetMsecTime() - m_autoTimer > 4000) {
                m_claw->cubeLaunch();
                m_autoState++;
            }
            break;
        default:
            break;
    }
}

void CenterSwitchAuto::Reset(void) {
}
}
