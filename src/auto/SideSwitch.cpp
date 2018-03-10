#include "src/auto/SideSwitch.h"
#include "src/auto/profiles/rightsideswitch_trajectory.h"
#include "src/auto/profiles/leftsideswitch_trajectory.h"
#include "src/auto/profiles/leftsideswitchbackoff_trajectory.h"
#include "src/auto/profiles/rightsideswitchbackoff_trajectory.h"

using namespace frc;
using namespace left_side_switch;
using namespace right_side_switch;
using namespace right_side_switch_backoff;
using namespace left_side_switch_backoff;
//        { "x": 106, "y": -60, "angle": 0 }

namespace frc973 {
SideSwitch::SideSwitch(Drive *drive, Elevator *elevator, Intake *intake,
                       Claw *claw)
        : m_drive(drive)
        , m_elevator(elevator)
        , m_intake(intake)
        , m_claw(claw)
        , m_autoTimer(0) {
}

SideSwitch::~SideSwitch() {
}

void SideSwitch::Execute(AutoRoutineBase::AutoDirection direction) {
    switch (m_autoState) {
        case 0:
            if (direction == AutoRoutineBase::AutoDirection::Left) {
                m_drive->SplineDrive(&left_side_switch::left_side_switch,
                                     Drive::RelativeTo::Now);
            }
            else if (direction == AutoRoutineBase::AutoDirection::Right) {
                m_drive->SplineDrive(&right_side_switch::right_side_switch,
                                     Drive::RelativeTo::Now);
            }
            m_intake->Open();
            m_intake->LowerIntake();
            m_elevator->SetPosition(Elevator::LOW_GOAL);
            m_claw->grab();
            m_claw->kickOff();
            m_autoTimer = GetMsecTime();
            m_autoState++;
            break;
        case 1:
            if (GetMsecTime() - m_autoTimer > 2000) {
                m_intake->RaiseIntake();
                m_autoTimer = GetMsecTime();
                m_autoState++;
            }
            break;
        case 2:
            if (m_drive->GetSplinePercentComplete() > 0.8 ||
                m_drive->OnTarget() || GetMsecTime() - m_autoTimer > 4000) {
                m_claw->cubeLaunch();
                m_autoState++;
            }
            break;
        case 3:
            if (m_drive->GetSplinePercentComplete() > 1.0) {
                if (direction == AutoRoutineBase::AutoDirection::Left) {
                    m_drive->SplineDrive(
                        &left_side_switch_backoff::left_side_switch_backoff,
                        Drive::RelativeTo::Now);
                }
                else if (direction == AutoRoutineBase::AutoDirection::Right) {
                    m_drive->SplineDrive(
                        &right_side_switch_backoff::right_side_switch_backoff,
                        Drive::RelativeTo::Now);
                }
                m_autoState++;
            }
            break;
        case 4:
            if (m_drive->GetSplinePercentComplete() > 1.0) {
                m_drive->OpenloopArcadeDrive(0.0, 0.0);
                m_autoState++;
            }
            break;
        default:
            break;
    }
}

void SideSwitch::Reset() {
}
}
