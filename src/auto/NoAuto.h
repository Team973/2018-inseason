#pragma once

#include "WPILib.h"
#include <iostream>
#include "src/auto/AutoRoutineBase.h"

using namespace frc;
namespace frc973 {
class NoAuto : public AutoRoutineBase {
public:
    NoAuto();
    virtual ~NoAuto();

    void Reset() override;
};
};
