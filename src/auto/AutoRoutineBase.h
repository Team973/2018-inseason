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

    enum class RobotStartPosition
    {
        Left,
        Center,
        Right
    };

    AutoRoutineBase();
    virtual ~AutoRoutineBase();

    virtual void Execute(AutoDirection direction);

    virtual void Reset();

protected:
    int m_autoState;
};
};
