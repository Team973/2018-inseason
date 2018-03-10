#include "src/auto/TwoCubeAuto.h"
#include "src/auto/profiles/rightscale_trajectory.h"
#include "src/auto/profiles/leftscale_trajectory.h"
#include "src/auto/profiles/twocubebackoffleft_trajectory.h"
#include "src/auto/profiles/twocubebackoffright_trajectory.h"
#include "src/auto/profiles/twocubeintakingleft_trajectory.h"
#include "src/auto/profiles/twocubeintakingright_trajectory.h"

using namespace frc;
using namespace left_scale;
using namespace right_scale;
using namespace two_cube_backoff_left;
using namespace two_cube_backoff_right;
using namespace two_cube_intaking_left;
using namespace two_cube_intaking_right;

namespace frc973 {
TwoCubeAuto::TwoCubeAuto(Drive *drive, Elevator *elevator, Intake *intake,
                         Claw *claw)
        : m_drive(drive)
        , m_elevator(elevator)
        , m_intake(intake)
        , m_claw(claw)
        , m_autoTimer(0) {
}

TwoCubeAuto::~TwoCubeAuto() {
}

void TwoCubeAuto::Execute(AutoRoutineBase::AutoDirection direction) {
    std::cout << "Scale Auto" << std::endl;
    switch (m_autoState) {
        case 0:
            if (direction == AutoRoutineBase::AutoDirection::Left) {
                m_drive->SplineDrive(&left_scale::left_scale,
                                     Drive::RelativeTo::Now);
            }
            else if (direction == AutoRoutineBase::AutoDirection::Right) {
                m_drive->SplineDrive(&right_scale::right_scale,
                                     Drive::RelativeTo::Now);
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
                m_elevator->SetPosition(Elevator::SCALE_HIGH);
                m_autoState++;
            }
            break;
        case 2:
            if (m_drive->GetSplinePercentComplete() > 0.8 ||
                m_drive->OnTarget()) {
                m_claw->cubeLaunch();
                m_autoTimer = GetMsecTime();
                m_autoState++;
            }
            break;
        case 3:
            if (GetMsecTime() - m_autoTimer > 500) {
                if (direction == AutoRoutineBase::AutoDirection::Left) {
                    m_drive->SplineDrive(
                        &two_cube_backoff_left::two_cube_backoff_left,
                        Drive::RelativeTo::SetPoint);
                }
                else if (direction == AutoRoutineBase::AutoDirection::Right) {
                    m_drive->SplineDrive(
                        &two_cube_backoff_right::two_cube_backoff_right,
                        Drive::RelativeTo::SetPoint);
                }
                m_elevator->SetPosition(Elevator::GROUND);
                m_autoTimer = GetMsecTime();
                m_autoState++;
            }
            break;
        case 4:
            if (m_drive->OnTarget() ||
                m_drive->GetSplinePercentComplete() > 1.0) {
                if (direction == AutoRoutineBase::AutoDirection::Left) {
                    m_drive->SplineDrive(
                        &two_cube_intaking_left::two_cube_intaking_left,
                        Drive::RelativeTo::Now);
                }
                else if (direction == AutoRoutineBase::AutoDirection::Right) {
                    m_drive->SplineDrive(
                        &two_cube_intaking_right::two_cube_intaking_right,
                        Drive::RelativeTo::Now);
                }
                m_intake->Open();
                m_intake->LowerIntake();
                m_intake->RegularPull();
                m_claw->open();
                m_claw->kickOff();
                m_autoTimer = GetMsecTime();
                m_autoState++;
            }
            break;
        case 5:
            if (m_drive->GetSplinePercentComplete() > 1.0) {
                m_intake->Close();
            }
            if (m_intake->IsCubeIn() &&
                ((m_drive->GetSplinePercentComplete() > 0.8) ||
                 GetMsecTime() - m_autoTimer > 4000)) {
                m_intake->Stop();
                m_intake->Open();
                m_intake->LowerIntake();
                m_claw->grab();
                m_claw->kickOff();
                m_autoState++;
            }
            break;
        case 6:
            m_elevator->SetPosition(Elevator::LOW_GOAL);
            if (m_elevator->GetPosition() > 20.0) {
                m_claw->cubeLaunch();
                m_autoState++;
            }
            break;
        default:
            break;
    }
}

void TwoCubeAuto::Reset() {
}
};
