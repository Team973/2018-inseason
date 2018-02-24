#pragma once

#include "WPILib.h"
#include <iostream>
#include "src/auto/AutoRoutineBase.h"

using namespace frc;
namespace frc973 {
class Disabled;

class ScaleAuto : public AutoRoutineBase {
public:
    ScaleAuto(void);
    virtual ~ScaleAuto(void);

    void Execute(AutoRoutineBase::AutoDirection direction) override;

    void Reset(void);
};
};
