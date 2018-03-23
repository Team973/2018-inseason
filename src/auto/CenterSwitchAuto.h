#pragma once

#include "WPILib.h"
#include <iostream>
#include "src/auto/AutoRoutineBase.h"
#include "src/subsystems/Drive.h"
#include "src/subsystems/Elevator.h"
#include "src/subsystems/Wrist.h"

using namespace frc;
namespace frc973 {
class CenterSwitchAuto : public AutoRoutineBase {
public:
    CenterSwitchAuto(Drive *drive, Elevator *elevator, Wrist *wrist);
    virtual ~CenterSwitchAuto();

    void Execute(AutoRoutineBase::AutoDirection direction) override;

    void Reset() override;

private:
    Drive *m_drive;
    Elevator *m_elevator;
    Wrist *m_wrist;

    uint32_t m_autoTimer;
};
};
