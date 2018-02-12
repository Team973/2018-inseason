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
    this->minColor = minColor;
    this->maxColor = maxColor;
    this->minVal = minVal;
    this->maxVal = maxVal;
}

void LinearScale::updateValue(double value) {
    this->currentValue = value;
}

void LinearScale::tick(PixelState& state) {
    PixelStateProcessorModulator::tick(state);
    uint8_t ledsToFill =
        std::fmin((currentValue - minVal) / (maxVal - minVal) * state.numLEDs,
                  state.numLEDs);
    for (unsigned int i = 0; i < ledsToFill; i++) {
        state.pixels.at(i) =
            minColor.gradientTo(maxColor, ((double)i / state.numLEDs));
    }
}
