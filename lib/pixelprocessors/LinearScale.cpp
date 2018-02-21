/*
 * LinearScale.cpp
 *
 *  Created on: Feb 12, 2018
 *      Author: Cole Brinsfield
 */

#include "LinearScale.h"

LinearScale::LinearScale(Color minColor, Color maxColor, double minVal,
                         double maxVal, PixelStateProcessor* modulator) {
    this->processor = modulator;
    this->m_minColor = minColor;
    this->m_maxColor = maxColor;
    this->m_minVal = minVal;
    this->m_maxVal = maxVal;
}

void LinearScale::updateValue(double value) {
    this->m_currentValue = value;
}

void LinearScale::tick(PixelState& state) {
    PixelStateProcessorModulator::tick(state);
    uint8_t ledsToFill = std::fmin(
        (m_currentValue - m_minVal) / (m_maxVal - m_minVal) * state.numLEDs,
        state.numLEDs);
    for (unsigned int i = 0; i < ledsToFill; i++) {
        state.pixels.at(i) =
            m_minColor.gradientTo(m_maxColor, ((double)i / state.numLEDs));
    }
}
