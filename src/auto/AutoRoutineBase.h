#pragma once

#include "WPILib.h"
#include <iostream>

using namespace frc;

namespace frc973 {
class AutoRoutineBase {
public:
    enum AutoDirection
    {
        Left,
        Right
    };
    AutoRoutineBase();
    virtual ~AutoRoutineBase();

    virtual void Execute(AutoDirection direction);

    virtual void Reset(void);

protected:
    int m_autoState;
};
};
