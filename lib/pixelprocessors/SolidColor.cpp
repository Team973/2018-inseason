/*
 * SolidColor.cpp
 *
 *  Created on: Feb 10, 2018
 *      Author: Cole Brinsfield
 */

#include "SolidColor.h"

namespace LightPattern {
SolidColor::SolidColor() {
    SolidColor(Color{0, 255, 0});
}
SolidColor::SolidColor(Color color) {
    m_currentColor = color;
}
void SolidColor::setColor(Color color) {
    m_currentColor = color;
}

void SolidColor::tick(PixelState& state) {
    std::fill(state.pixels.begin(), state.pixels.end(), m_currentColor);
}
}
