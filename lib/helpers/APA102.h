/*
 * APA102.h
 *  Created on: Feb 5, 2018
 *      Author: Cole Brinsfield
 */
#ifndef SRC_MODULES_APA102_H_
#define SRC_MODULES_APA102_H_
#include <stdint.h>
#include "WPILib.h"
#include "lib/pixelprocessors/GreyLightTypes.h"
#include <cmath>
class APA102 {
public:
    APA102(int numLEDs, frc::SPI::Port port = frc::SPI::Port::kMXP);
    void show(std::vector<Color> pixels);

private:
    uint8_t startFrame[4] = {0x00, 0x00, 0x00, 0x00};
    uint8_t endFrame[4] = {0xFF, 0xFF, 0xFF, 0xFF};
    int numLEDs;
    const int globalOffset = 0;
    const int blueOffset = 1;
    const int redOffset = 3;
    const int greenOffset = 2;
    const int bytesPerLED = 4;
    const int led0Offset = 4;  // length of startFrame
    int endFrameOffset;        // will be dependent on num Leds
    frc::SPI::Port port;
    frc::SPI* spi;
    const int SPI_CLK_RATE = 13000000;
    std::vector<uint8_t> ledBuffer;
    const int ledMaxVal = 255;
};

#endif
