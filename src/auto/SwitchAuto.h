#pragma once

#include "WPILib.h"
#include <iostream>
#include "src/auto/AutoRoutine.h"

using namespace frc;
namespace frc973 {
class SwitchAuto : public AutoRoutine {
public:
    SwitchAuto(void);
    virtual ~SwitchAuto(void);

    void Execute(void) override;
    void Reset(void);
};
};
