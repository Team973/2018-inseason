#pragma once

#include "WPILib.h"
#include <iostream>
#include "src/auto/AutoRoutineBase.h"
#include "src/subsystems/Drive.h"
#include "src/subsystems/Claw.h"
#include "src/subsystems/IntakeAssembly.h"

using namespace frc;
namespace frc973 {
class CenterSwitchAuto : public AutoRoutineBase {
public:
    CenterSwitchAuto(Drive *drive, IntakeAssembly *intakeAssembly);
    virtual ~CenterSwitchAuto();

    void Execute(AutoRoutineBase::AutoDirection direction) override;

    void Reset() override;

private:
    Drive *m_drive;
    IntakeAssembly *m_intakeAssembly;

    uint32_t m_autoTimer;
};
};
