/*
 * Siren.cpp
 *
 *  Created on: Feb 10, 2018
 *      Author: Cole Brinsfield
 */

#include "Siren.h"

namespace LightPattern {

Siren::Siren(Color first, Color second, int frameDuration)
        : m_first(first), m_second(second), m_frameDuration(frameDuration) {
}

void Siren::SetColors(Color first, Color second) {
    this->m_first = first;
    this->m_second = second;
}

void Siren::SetFrameDuration(int frameDuration) {
    this->m_frameDuration = frameDuration;
}

void Siren::Tick(PixelState& state) {
    if (state.frame % m_frameDuration == 0)
        m_color = !m_color;
    if (m_color) {
        std::fill(state.pixels.begin(), state.pixels.end(), m_first);
    }
    else {
        std::fill(state.pixels.begin(), state.pixels.end(), m_second);
    }
}
}
