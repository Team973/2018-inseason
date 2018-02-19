#include "APA102.h"
#include <iostream>
APA102::APA102(int numLEDs, frc::SPI::Port port)
        : numLEDs(numLEDs), port(port) {
    int numBytesForStrip =
        4 * numLEDs + 4 + 4;  // 4*numLeds+startFrame length + endFrame length
    endFrameOffset = 4 * numLEDs + 4;  // 4*numLEDs+startFrame length;
    ledBuffer = std::vector<uint8_t>(numBytesForStrip);
    /*
     * One frame of led data consists of four 0x00 bytes, sequential 0xFF, R, G,
     * B for each LED, and then 4 0xFF bytes
     */
    for (int i = 0; i < 4; i++) {
        ledBuffer.at(i) = startFrame[i];
    }
    for (int i = 0; i < 4; i++) {
        ledBuffer.at(i + endFrameOffset) = endFrame[i];
    }
    spi = new frc::SPI(port);
    spi->SetMSBFirst();
    spi->SetClockActiveLow();
    spi->SetClockRate(SPI_CLK_RATE);
    spi->SetSampleDataOnFalling();
}

void APA102::show(std::vector<Color> pixels) {
    int CHUNK_SIZE = 127;  // max TX size
    for (int i = 0; i < numLEDs; i++) {
        ledBuffer.at(i * bytesPerLED + led0Offset + globalOffset) = 0xFF;
        ledBuffer.at(i * bytesPerLED + led0Offset + redOffset) = pixels.at(i).r;
        ledBuffer.at(i * bytesPerLED + led0Offset + greenOffset) =
            pixels.at(i).g;
        ledBuffer.at(i * bytesPerLED + led0Offset + blueOffset) =
            pixels.at(i).b;
    }
    int ledBufferLength = ledBuffer.size();
    for (int offset = 0; offset < ledBufferLength; offset += CHUNK_SIZE) {
        int startIndex = offset;
        int endIndex = std::min(offset + CHUNK_SIZE, ledBufferLength);
        int size = endIndex - startIndex;
        uint8_t txArray[size];
        for (int i = 0; i < size; i++) {
            txArray[i] = ledBuffer.at(startIndex + i);
        }
        spi->Write(txArray, size);
    }
}
