#pragma once

#include "WPILib.h"
#include <iostream>
#include "src/auto/AutoRoutineBase.h"
#include "src/subsystems/Drive.h"
#include "src/subsystems/IntakeAssembly.h"

using namespace frc;
namespace frc973 {
class Disabled;

class TwoCubeAuto : public AutoRoutineBase {
public:
    TwoCubeAuto(Drive *drive, IntakeAssembly *intakeAssembly);
    virtual ~TwoCubeAuto();

    void Execute(AutoRoutineBase::AutoDirection direction) override;

    void Reset() override;

private:
    Drive *m_drive;
    IntakeAssembly *m_intakeAssembly;

    uint32_t m_autoTimer;
};
};
