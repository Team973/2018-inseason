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

    void ExecuteLeft(void) override;
    void ExecuteRight(void) override;

    void Reset(void);
};
};
