#pragma once

#include "WPILib.h"
#include <iostream>
#include "src/auto/AutoRoutineBase.h"
#include "src/subsystems/Drive.h"
#include "src/subsystems/Claw.h"
#include "src/subsystems/IntakeAssembly.h"

using namespace frc;
namespace frc973 {

/**
 * Center Switch auto.
 */
class CenterSwitchAuto : public AutoRoutineBase {
public:
    /**
     * Construct a Center Switch auto.
     * @param drive Drive subsystem.
     * @param intakeAssembly Intake Assembly Subsytstem.
     */
    CenterSwitchAuto(Drive *drive, IntakeAssembly *intakeAssembly);
    virtual ~CenterSwitchAuto();

    /**
     * Called every robot cycle, runs state machine.
     * @param direction Side of switch/Scale to score on.
     * @param scalePos The scale position.
     */
    void Execute(AutoRoutineBase::AutoDirection direction,
                 std::string scalePos) override;

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
