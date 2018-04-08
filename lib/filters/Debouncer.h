/*
 * Debouncer.h  Copied from 254.  Don't tell no one
 *
 * Filters a digital signal... if the incoming signal has been false at any
 * point in the last |period|, return false.  If it has been true for the
 * whole |period|, return true.  Helpful for OnTarget and IsFinished type
 * functions.
 *
 *  Created on: Jan 17, 2016
 *      Author: Andrew
 */

#pragma once

#include "lib/util/Util.h"

namespace frc973 {

/**
 * Interface for something that needs this filter to debounce values.
 */
class Debouncer {
public:
    /**
     * Create a Debouncer object with the given period in seconds.
     * @param period Time to check for falses.
     */
    Debouncer(double period);
    virtual ~Debouncer();

    /**
     * Calculate the filtered value given the original datapoint.
     * @param val The current data point that needs to be filtered.
     * @return Result of filtering calculation.
     */
    bool Update(bool val);

private:
    double m_timeStart;
    double m_period;
    bool m_first;
};
}
