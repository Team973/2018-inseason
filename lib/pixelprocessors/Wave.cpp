/*
 * Wave.cpp
 *
 *  Created on: February 13, 2018
 *      Author: Cole Brinsfield
 */

#include "Wave.h"
Wave::Wave(Color background, Color foreground, int period) {
    this->m_foreground = foreground;
    this->m_background = background;
    this->g_period = period;
}

void Wave::tick(PixelState& state) {
    for (unsigned int i = 0; i < state.numLEDs; i++) {
        state.pixels.at(i) = m_background;
    }

    for (unsigned int i = 0; i < state.numLEDs; i++) {
        state.pixels.at(i) = m_background.gradientTo(
            m_foreground,
            (cos((i + state.frame) * (2 * M_PI / g_period)) + 1) / 2);
    }
}
