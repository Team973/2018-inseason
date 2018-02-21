/*
 * APA102.h
 *  Created on: Feb 5, 2018
 *      Author: Cole Brinsfield
 */
#ifndef SRC_MODULES_APA102_H_
#define SRC_MODULES_APA102_H_
#include <stdint.h>
#include "WPILib.h"
#include <algorithm>
#include "lib/pixelprocessors/GreyLightTypes.h"
#include <cmath>
class APA102 {
public:
    APA102(int numLEDs, frc::SPI::Port port = frc::SPI::Port::kMXP);
    void show(std::vector<Color> pixels);

private:
    uint8_t m_startFrame[4] = {0x00, 0x00, 0x00, 0x00};
    uint8_t m_endFrame[4] = {0xFF, 0xFF, 0xFF, 0xFF};
    int m_numLEDs;
    const int m_globalOffset = 0;
    const int m_blueOffset = 1;
    const int m_redOffset = 3;
    const int m_greenOffset = 2;
    const int m_bytesPerLED = 4;
    const int m_led0Offset = 4;  // length of startFrame
    int m_endFrameOffset;        // will be dependent on num Leds
    frc::SPI* m_spi;
    const int SPI_CLK_RATE = 13000000;
    std::vector<uint8_t> m_ledBuffer;
};

#endif
