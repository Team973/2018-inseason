/*
 * GreyLightTypes.h
 *
 *  Created on: Feb 5, 2018
 *      Author: Cole Brinsfield
 */

#ifndef SRC_MODULES_GREYLIGHTTYPES_H_
#define SRC_MODULES_GREYLIGHTTYPES_H_
#include <cstdint>
#include <cmath>
#include <vector>

namespace GreyLightType {

struct Color {
    // 0-255
    uint8_t r;
    uint8_t g;
    uint8_t b;

    Color gradientTo(Color other, double percentR, double percentG,
                     double percentB) const {
        return Color{
            uint8_t(r + (other.r - r) * percentR),
            uint8_t(g + (other.g - g) * percentG),
            uint8_t(b + (other.b - b) * percentB),
        };
    }
    Color gradientTo(Color other, double percent) const {
        return gradientTo(other, percent, percent, percent);
    }
};

struct PixelState {
    // the current frame (+1 per tick)
    unsigned int frame;

    // framerate
    unsigned int fps;

    unsigned int numLEDs;

    // time in milliseconds since last tick
    unsigned int delta;

    // the array of pixels (this gets displayed)
    std::vector<Color> pixels;
};
}
#endif /* SRC_MODULES_GREYLIGHTTYPES_H_ */
