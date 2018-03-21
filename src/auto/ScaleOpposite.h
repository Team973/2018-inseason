#pragma once

#include "WPILib.h"
#include <iostream>
#include "src/auto/AutoRoutineBase.h"
#include "src/subsystems/Drive.h"
#include "src/subsystems/Elevator.h"
#include "src/subsystems/Claw.h"

using namespace frc;
namespace frc973 {
class Disabled;

class ScaleOpposite : public AutoRoutineBase {
public:
    ScaleOpposite(Drive *drive, Elevator *elevator, Claw *claw);
    virtual ~ScaleOpposite();

    void Execute(AutoRoutineBase::AutoDirection direction) override;

    void Reset() override;

private:
    Drive *m_drive;
    Elevator *m_elevator;
    Claw *m_claw;

    uint32_t m_autoTimer;
};
};
