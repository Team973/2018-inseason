/*
 * PixelChase.cpp
 *
 *  Created on: Feb 10, 2018
 *      Author: Cole Brinsfield
 */

#include "PixelChase.h"

PixelChase::PixelChase(PixelStateProcessor* processor, Color background) {
    this->processor = processor;
    this->background = background;
}

void PixelChase::tick(PixelState& state) {
    PixelStateProcessorModulator::tick(state);

    uint16_t frame = getFrame(state.frame);

    int k;
    for (std::size_t i = 0; i < state.numLEDs; i++) {
        k = i % 16;
        if ((frame & (1 << k)) >
            0) {  // get the kth bit of frame, if its 1 (OFF)
            state.pixels.at(i) =
                background;  // set the pixel in that position to off
        }
    }
}

// 0 is led ON, 1 is led OFF
uint16_t PixelChase::getFrame(int n) {
    int k = n % 16;
    uint8_t used;
    if (k < 8) {  // n 0-8
        // I want the first n bits of 2nd to be 1, the rest 0
        used = 255 >> (k + 1);
    }
    else {  // 9 to 16, 17 - n is from 8-0
        used = 255 << (16 - k);
    }

    if (n % 32 < 16) {
        return (0xff00 ^
                used);  // return first word all off, second word is animation
    }
    else {
        return ((used << 8) ^ 0x00ff);
    }
}
