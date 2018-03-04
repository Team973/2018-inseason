#include "src/auto/TwoCubeAuto.h"
#include "src/auto/profiles/rightscale_trajectory.h"
#include "src/auto/profiles/leftscale_trajectory.h"
#include "src/auto/profiles/righttwocube_trajectory.h"
#include "src/auto/profiles/lefttwocube_trajectory.h"

using namespace frc;

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
                m_drive->SplineDrive(&left_scale::left_scale);
            }
            else if (direction == AutoRoutineBase::AutoDirection::Right) {
                m_drive->SplineDrive(&right_scale::right_scale);
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
                m_autoTimer = GetMsecTime();
                m_autoState++;
            }
            break;
        case 2:
            if (m_drive->GetSplinePercentComplete() > 0.95 ||
                m_drive->OnTarget() || GetMsecTime() - m_autoTimer > 5000) {
                m_claw->cubeLaunch();
                m_autoState++;
            }
            break;
        case 3:
            m_drive->PIDDrive(0.0, 180.0, Drive::RelativeTo::Now, 0.8);
            m_elevator->SetPosition(Elevator::GROUND);
            m_autoTimer = GetMsecTime();
            m_autoState++;
            break;
        case 4:
            if (m_drive->OnTarget() || GetMsecTime() - m_autoTimer > 2000) {
                if (direction == AutoRoutineBase::AutoDirection::Left) {
                    m_drive->SplineDrive(&left_two_cube::left_two_cube);
                }
                else if (direction == AutoRoutineBase::AutoDirection::Right) {
                    m_drive->SplineDrive(&right_two_cube::right_two_cube);
                }
            }
            m_intake->Close();
            m_intake->LowerIntake();
            m_intake->RegularPull();
            m_claw->open();
            m_claw->kickOff();
            m_autoTimer = GetMsecTime();
            m_autoState++;
            break;
        case 5:
            if (m_intake->IsCubeIn() &&
                ((m_drive->GetSplinePercentComplete() > 0.95) ||
                 m_drive->OnTarget() || GetMsecTime() - m_autoTimer > 3000)) {
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
            if (m_elevator->GetPosition() > 14.0) {
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
