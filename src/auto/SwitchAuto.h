#pragma once

#include "WPILib.h"
#include <iostream>
#include "src/auto/AutoRoutine.h"
#include "src/subsystems/Drive.h"

using namespace frc;
namespace frc973 {
class SwitchAuto : public AutoRoutine {
public:
    SwitchAuto(Drive *drive);
    virtual ~SwitchAuto(void);

    void Execute(void) override;
    void Reset(void);

private:
    Drive *m_drive;
};
};
