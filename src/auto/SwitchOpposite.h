#pragma once

#include "WPILib.h"
#include <iostream>
#include "src/auto/AutoRoutineBase.h"
#include "src/subsystems/Drive.h"
#include "src/subsystems/IntakeAssembly.h"

using namespace frc;
namespace frc973 {
class Disabled;

/**
 * Switch Opposite auto.
 */
class SwitchOpposite : public AutoRoutineBase {
public:
    /**
     * Construct a Switch Opposite auto.
     * @param drive Drive subsystem.
     * @param intakeAssembly Intake Assembly Subsytstem.
     */
    SwitchOpposite(Drive *drive, IntakeAssembly *intakeAssembly);
    virtual ~SwitchOpposite();

    /**
     * Called every robot cycle, runs state machine.
     * @param direction Side of switch/Scale to score on.
     */
    void Execute(AutoRoutineBase::AutoDirection direction) override;

    /**
     * Resets the auto to the beginning.
     */
    void Reset() override;

private:
    Drive *m_drive;
    IntakeAssembly *m_intakeAssembly;

    uint32_t m_autoTimer;
};
};
