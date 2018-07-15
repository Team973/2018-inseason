#pragma once

#include "WPILib.h"
#include <iostream>
#include "src/auto/AutoRoutineBase.h"
#include "src/subsystems/Drive.h"
#include "src/subsystems/IntakeAssembly.h"
#include "src/controllers/PIDDriveController.h"

using namespace frc;
namespace frc973 {
class Disabled;

class ScaleAuto : public AutoRoutineBase {
public:
    ScaleAuto(Drive *drive, IntakeAssembly *intakeAssembly);
    virtual ~ScaleAuto();

    void Execute(AutoRoutineBase::AutoDirection direction,
                 std::string scalePos) override;

    void Reset() override;

private:
    Drive *m_drive;
    IntakeAssembly *m_intakeAssembly;

    uint32_t m_autoTimer;
};
};
