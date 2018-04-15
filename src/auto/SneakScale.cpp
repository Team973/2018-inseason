#include "src/auto/SneakScale.h"
#include "src/auto/profiles/rightsneak_trajectory.h"
#include "src/auto/profiles/leftsneak_trajectory.h"

using namespace frc;
using namespace left_sneak;
using namespace right_sneak;

namespace frc973 {
SneakScale::SneakScale(Drive *drive, IntakeAssembly *intakeAssembly)
        : m_drive(drive), m_intakeAssembly(intakeAssembly), m_autoTimer(0) {
}

SneakScale::~SneakScale() {
}

void SneakScale::Execute(AutoRoutineBase::AutoDirection direction,
                         std::string scalePos) {
    std::cout << "Scale Auto" << std::endl;
    switch (m_autoState) {
        case 0:
            if (scalePos == "L") {
                m_drive->SplineDrive(&left_sneak::left_sneak,
                                     Drive::RelativeTo::Now);
            }
            else {
                m_drive->SplineDrive(&right_sneak::right_sneak,
                                     Drive::RelativeTo::Now);
            }
            m_autoTimer = GetMsecTime();
            m_autoState++;
            break;
        case 1:
            if (m_drive->GetSplinePercentComplete() > 0.4) {
                m_intakeAssembly->GoToIntakePosition(
                    IntakeAssembly::SCALE_HIGH_PRESET);
                m_autoTimer = GetMsecTime();
                m_autoState++;
            }
            break;
        case 2:
            if (m_drive->GetSplinePercentComplete() > 1.0 ||
                GetMsecTime() - m_autoTimer > 4000) {
                m_intakeAssembly->GoToIntakePosition(
                    IntakeAssembly::IntakePreset(Elevator::SCALE_HIGH,
                                                 Wrist::EXTENDED));
                m_autoTimer = GetMsecTime();
                m_autoState++;
            }
            break;
        case 3:
            if (GetMsecTime() - m_autoTimer > 500) {
                m_intakeAssembly->EjectCube();
            }
            if (GetMsecTime() - m_autoTimer > 1000) {
                m_drive->PIDDrive(-24.0, 0.0, Drive::RelativeTo::Now, 0.5);
                m_autoTimer = GetMsecTime();
                m_autoState++;
            }
            break;
        case 4:
            if (GetMsecTime() - m_autoTimer > 1000) {
                m_intakeAssembly->StopIntake();
                m_intakeAssembly->GoToIntakePosition(
                    IntakeAssembly::IntakePreset(Elevator::GROUND,
                                                 Wrist::STOW));
                m_autoTimer = GetMsecTime();
                m_autoState++;
            }
            break;
        default:
            break;
    }
}

void SneakScale::Reset() {
}
};
