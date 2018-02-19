/*
 * GreyLight.h
 *
 *  Created on: Feb 5, 2018
 *      Author: Cole Brinsfield
 */
#ifndef SRC_MODULES_GREYLIGHT_H_
#define SRC_MODULES_GREYLIGHT_H_

#include <chrono>
#include <mutex>
#include <thread>
#include "lib/pixelprocessors/GreyLightTypes.h"
#include "lib/helpers/APA102.h"
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
    APA102* strip;
    std::thread worker;
};

#endif /* SRC_MODULES_GREYLIGHT_H_ */
