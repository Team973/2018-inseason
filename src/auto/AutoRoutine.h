#pragma once

#include "WPILib.h"
#include <iostream>

using namespace frc;

namespace frc973 {
class AutoRoutine {
public:
    AutoRoutine();
    virtual ~AutoRoutine();

    virtual void Execute(void);
    virtual void Reset(void);

protected:
    int m_autoState;
};
};
