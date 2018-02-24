#pragma once

#include "WPILib.h"
#include <iostream>
#include "src/auto/AutoRoutineBase.h"
#include "src/subsystems/Drive.h"
#include "src/subsystems/Elevator.h"
#include "src/subsystems/Claw.h"
#include "src/subsystems/Intake.h"

using namespace frc;
namespace frc973 {
class SideSwitch : public AutoRoutineBase {
public:
    SideSwitch(Drive *drive, Elevator *elevator, Intake *intake, Claw *claw);
    virtual ~SideSwitch(void);

    void Execute(AutoRoutineBase::AutoDirection direction) override;

    void Reset(void);

private:
    Drive *m_drive;
    Elevator *m_elevator;
    Intake *m_intake;
    Claw *m_claw;

    uint32_t m_autoTimer;
};
};
