#pragma once

#include "WPILib.h"
#include <iostream>

using namespace frc;

namespace frc973 {

/**
 * Auto Routine base.
 */
class AutoRoutineBase {
public:
    /**
     * The side for the auto to set as a goal.
     */
    enum AutoDirection
    {
        Left, /**< Left goal. */
        Right /**< Right goal. */
    };

    /**
     * Robot start position against the driver station wall.
     */
    enum class RobotStartPosition
    {
        Left,   /**< Left side of alliance wall. */
        Center, /**< Center of alliance wall. */
        Right   /**< Right side of alliance wall. */
    };

    /**
     * Construct a Auto Routine base.
     */
    AutoRoutineBase();
    virtual ~AutoRoutineBase();

    /**
     * Called every robot cycle, runs state machine. Overwritten by child class.
     * @param direction The side of switch/Scale to score on.
     * @param scalePos The scale position.
     */
    virtual void Execute(AutoDirection direction, std::string scalePos);

    /**
     * Resets the auto to the beginning.
     */
    virtual void Reset();

protected:
    /**
     * Current step of the auto routine.
     */
    int m_autoState;
};
};
