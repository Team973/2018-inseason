#pragma once

#include "WPILib.h"
#include <iostream>
#include "src/auto/AutoRoutineBase.h"
#include "src/subsystems/Drive.h"

using namespace frc;
namespace frc973 {

/**
 * Forward auto.
 */
class ForwardAuto : public AutoRoutineBase {
public:
    /**
     * Construct a Forward auto.
     * @param drive Drive subsystem.
     */
    ForwardAuto(Drive *drive);
    virtual ~ForwardAuto();

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
};
};
