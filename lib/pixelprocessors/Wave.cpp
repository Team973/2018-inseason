/*
 * Wave.cpp
 *
 *  Created on: February 13, 2018
 *      Author: Cole Brinsfield
 */

#include "Wave.h"
Wave::Wave(Color background, Color foreground, int period) {
    this->foreground = foreground;
    this->background = background;
    this->period = period;
    this->offset = 0;
}

void Wave::tick(PixelState& state) {
    for (unsigned int i = 0; i < state.numLEDs; i++) {
        state.pixels.at(i) = background;
    }

    for (unsigned int i = 0; i < state.numLEDs; i++) {
        state.pixels.at(i) = background.gradientTo(
            foreground, (cos((i + state.frame) * (2 * M_PI / period)) + 1) / 2);
    }
}
