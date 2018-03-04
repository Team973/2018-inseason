#include "src/auto/ScaleAuto.h"
#include "src/auto/profiles/rightscale_trajectory.h"
#include "src/auto/profiles/leftscale_trajectory.h"

using namespace frc;
using namespace left_scale;
using namespace right_scale;

namespace frc973 {
ScaleAuto::ScaleAuto(Drive *drive, Elevator *elevator, Intake *intake,
                     Claw *claw)
        : m_drive(drive)
        , m_elevator(elevator)
        , m_intake(intake)
        , m_claw(claw)
        , m_autoTimer(0) {
}

ScaleAuto::~ScaleAuto() {
}

void ScaleAuto::Execute(AutoRoutineBase::AutoDirection direction) {
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
            if (m_drive->GetSplinePercentComplete() > 0.80 ||
                m_drive->OnTarget() || GetMsecTime() - m_autoTimer > 4000) {
                m_claw->cubeLaunch();
                m_autoState++;
            }
            break;
        default:
            break;
    }
}

void ScaleAuto::Reset() {
}
};
