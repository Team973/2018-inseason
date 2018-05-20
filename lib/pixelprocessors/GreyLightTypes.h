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
/**
 * Data representation of a Color in (r,g,b) format.
 */
struct Color {
    // 0-255
    uint8_t r;
    uint8_t g;
    uint8_t b;
    /**
     * Generate an intermediate Color
     * @param other Color to gradient to.
     * @param percentR Percentage of r channel
     * @param percentG Percentage of g channel
     * @param percentB Percentage of b channel
     */
    Color gradientTo(Color other, double percentR, double percentG,
                     double percentB) const {
        return Color{
            uint8_t(r + (other.r - r) * percentR),
            uint8_t(g + (other.g - g) * percentG),
            uint8_t(b + (other.b - b) * percentB),
        };
    }
    /**
     * Generate an intermediate Color
     * @param other Color to gradient to.
     * @param percent Percentage of transition to generate
     */
    Color gradientTo(Color other, double percent) const {
        return gradientTo(other, percent, percent, percent);
    }
};
/**
 * Collection of parameters for each frame of data.
 */
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
