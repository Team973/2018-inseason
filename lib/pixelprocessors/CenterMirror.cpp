/*
 * CenterMirror.cpp
 *
 *  Created on: Feb 12, 2018
 *      Author: Cole Brinsfield
 */

#include "CenterMirror.h"
CenterMirror::CenterMirror(PixelStateProcessor* processor, bool inverse) {
    this->processor = processor;
    this->m_inverse = inverse;
}

void CenterMirror::tick(PixelState& state) {
    m_previousNumLEDs = state.numLEDs;
    state.numLEDs = state.numLEDs / 2;
    PixelStateProcessorModulator::tick(state);
    if (m_inverse) {
        pushToRightSide(state);
        std::reverse(state.pixels.begin(),
                     state.pixels.begin() + m_previousNumLEDs / 2);
    }
    else {
        pushToRightSide(state);
        std::reverse(state.pixels.begin() + m_previousNumLEDs / 2,
                     state.pixels.end());
    }
    state.numLEDs = m_previousNumLEDs;
}

void CenterMirror::pushToRightSide(PixelState& state) {
    for (std::size_t i = 0; i < m_previousNumLEDs / 2; i++) {
        state.pixels.at(m_previousNumLEDs / 2 + i) = state.pixels.at(i);
    }
}
