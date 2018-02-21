#pragma once

#include "WPILib.h"
#include <iostream>
#include "src/auto/AutoRoutine.h"
#include "src/subsystems/Drive.h"
#include "src/subsystems/Elevator.h"
#include "src/subsystems/Claw.h"
#include "src/subsystems/Intake.h"

using namespace frc;
namespace frc973 {
class SwitchAuto : public AutoRoutine {
public:
    SwitchAuto(Drive *drive, Elevator *elevator, Intake *intake, Claw *claw);
    virtual ~SwitchAuto(void);

    void Execute(void) override;
    void Reset(void);

private:
    Drive *m_drive;
    Elevator *m_elevator;
    Intake *m_intake;
    Claw *m_claw;

    int m_autoState;
    uint32_t m_autoTimer;
};
};
