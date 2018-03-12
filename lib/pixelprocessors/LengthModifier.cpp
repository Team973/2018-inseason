/*
 * LengthModifier.cpp
 *
 *  Created on: March 11, 2018
 *      Author: Cole Brinsfield
 */

#include "LengthModifier.h"
#include <iostream>
namespace LightPattern {
LengthModifier::LengthModifier(PixelStateProcessor* processor, int numLEDs) {
    this->processor = processor;
    m_numLEDS = numLEDs;
}
void LengthModifier::Tick(PixelState& state) {
    double previousNumLEDs = state.numLEDs;
    state.numLEDs = m_numLEDS;
    PixelStateProcessorModulator::Tick(state);
    state.numLEDs = previousNumLEDs;
}
}
