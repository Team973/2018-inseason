#pragma once

#include "WPILib.h"
#include <iostream>
#include "src/auto/AutoRoutineBase.h"
#include "src/subsystems/Drive.h"
#include "src/subsystems/IntakeAssembly.h"

using namespace frc;
namespace frc973 {
class SideSwitch : public AutoRoutineBase {
public:
    SideSwitch(Drive *drive, IntakeAssembly *intakeAssembly);
    virtual ~SideSwitch();

    void Execute(AutoRoutineBase::AutoDirection direction) override;

    void Reset() override;

private:
    Drive *m_drive;
    IntakeAssembly *m_intakeAssembly;

    uint32_t m_autoTimer;
};
};
