#pragma once

#include <WPILib.h>
#include <iostream>
#include "src/auto/AutoRoutine.h"

using namespace frc;
namespace frc973{
class ForwardAuto : public AutoRoutine {
    public:
        ForwardAuto(void);
        virtual ~ForwardAuto(void);

        void Execute(void) override;
        void Reset(void);
    };
};
