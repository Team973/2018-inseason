/*
 * Siren.cpp
 *
 *  Created on: Feb 10, 2018
 *      Author: Cole Brinsfield
 */

#include "Siren.h"

Siren::Siren(Color first, Color second, int frameDuration)
        : first(first), second(second), frameDuration(frameDuration) {
}

void Siren::setColors(Color first, Color second) {
    this->first = first;
    this->second = second;
}

void Siren::setFrameDuration(int frameDuration) {
    this->frameDuration = frameDuration;
}

void Siren::tick(PixelState& state) {
    if (state.frame % frameDuration == 0)
        color = !color;
    if (color) {
        std::fill(state.pixels.begin(), state.pixels.end(), first);
    }
    else
        std::fill(state.pixels.begin(), state.pixels.end(), second);
}
