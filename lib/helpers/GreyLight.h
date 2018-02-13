/*
 * GreyLight.h
 *
 *  Created on: Feb 5, 2018
 *      Author: Cole Brinsfield
 */
#ifndef SRC_MODULES_GREYLIGHT_H_
#define SRC_MODULES_GREYLIGHT_H_

// #include <Settings.h>
#include <chrono>
#include <mutex>
#include <thread>
#include "lib/pixelprocessors/GreyLightTypes.h"
#include "lib/pixelprocessors/PixelStateProcessor.h"

class GreyLight {
public:
    GreyLight(int numLEDs);

    void setPixelStateProcessor(PixelStateProcessor* processor);
    std::mutex stateLock;
    // only access with stateLock acquired
    PixelState state;
    void loop();
    PixelStateProcessor* processor;

private:
    void writeFrame(std::vector<Color> pixels);

    std::thread worker;
};

#endif /* SRC_MODULES_GREYLIGHT_H_ */
