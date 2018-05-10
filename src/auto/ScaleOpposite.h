#pragma once

#include "WPILib.h"
#include <iostream>
#include "src/auto/AutoRoutineBase.h"
#include "src/subsystems/Drive.h"
#include "src/subsystems/IntakeAssembly.h"
#include "src/controllers/PIDDriveController.h"

using namespace frc;
namespace frc973 {
class Disabled;

/**
 * Scale Opposite auto.
 */
class ScaleOpposite : public AutoRoutineBase {
public:
    /**
     * Construct a Scale Opposite auto.
     * @param drive Drive subsystem.
     * @param intakeAssembly Intake Assembly Subsytstem.
     */
    ScaleOpposite(Drive *drive, IntakeAssembly *intakeAssembly);
    virtual ~ScaleOpposite();

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
