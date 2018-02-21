#pragma once

#include "WPILib.h"
#include <iostream>
#include "src/auto/AutoRoutine.h"

using namespace frc;
namespace frc973 {
class ScaleAuto : public AutoRoutine {
public:
    ScaleAuto(void);
    virtual ~ScaleAuto(void);

    void Execute(void) override;
    void Reset(void);
};
};
