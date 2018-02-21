/*
 * Static.cpp
 *
 *  Created on: Feb 10, 2018
 *      Author: Cole Brinsfield
 */

#include "Static.h"

Static::Static() {
    Static(Color{0, 255, 0});
}
Static::Static(Color color) {
    m_currentColor = color;
}
void Static::setColor(Color color) {
    m_currentColor = color;
}

void Static::tick(PixelState& state) {
    std::fill(state.pixels.begin(), state.pixels.end(), m_currentColor);
}
