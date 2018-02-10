/*
 * Gradient.cpp
 *
 *  Created on: Feb 10, 2018
 *      Author: Cole Brinsfield
 */

#include "Gradient.h"

Gradient::Gradient(Color gradientStart, Color gradientEnd)
        : gradientStart(gradientStart), gradientEnd(gradientEnd) {
}

void Gradient::tick(PixelState& state) {
    for (std::size_t i = 0; i < state.numLEDs / 2; i++) {
        double percentage = double(i) / (state.numLEDs / 2);
        Color gradientIndex = {
            uint8_t(gradientStart.r +
                    percentage * (gradientEnd.r - gradientStart.r)),
            uint8_t(gradientStart.g +
                    percentage * (gradientEnd.g - gradientStart.g)),
            uint8_t(gradientStart.b +
                    percentage * (gradientEnd.b - gradientStart.b))};
        state.pixels.at(i) = gradientIndex;
        // std::cout<<"I: "<<i<<" PERCENTANGE 1/2: "<<percentage<<std::endl;
    }
    for (std::size_t i = state.numLEDs / 2; i < state.numLEDs; i++) {
        double percentage = double(i - state.numLEDs / 2) / (state.numLEDs / 2);
        Color gradientIndex = {
            uint8_t(gradientEnd.r +
                    percentage * (gradientStart.r - gradientEnd.r)),
            uint8_t(gradientEnd.g +
                    percentage * (gradientStart.g - gradientEnd.g)),
            uint8_t(gradientEnd.b +
                    percentage * (gradientStart.b - gradientEnd.b))};
        state.pixels.at(i) = gradientIndex;
        // std::cout<<"I: "<<i<<" PERCENTANGE 2/2: "<<percentage<<std::endl;
    }
}
