#pragma once

#include "WPILib.h"
#include <iostream>
#include "src/auto/AutoRoutine.h"

using namespace frc;
namespace frc973 {
class NoAuto : public AutoRoutine {
public:
    NoAuto(void);
    virtual ~NoAuto(void);

    void Execute(void) override;
    void Reset(void);
};
};
