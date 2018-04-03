#pragma once

#include "WPILib.h"
#include <iostream>
#include "src/auto/AutoRoutineBase.h"
#include "src/subsystems/Drive.h"

using namespace frc;
namespace frc973 {
class ForwardAuto : public AutoRoutineBase {
public:
    ForwardAuto(Drive *drive);
    virtual ~ForwardAuto();

    void Execute(AutoRoutineBase::AutoDirection direction) override;

    void Reset() override;

private:
    Drive *m_drive;
};
};
