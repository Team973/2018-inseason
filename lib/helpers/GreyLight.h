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

using namespace GreyLightType;
using namespace LightPattern;

class GreyLight {
public:
    GreyLight(int numLEDs);
    void SetPixelStateProcessor(PixelStateProcessor* processor);
    void Loop();

private:
    PixelStateProcessor* m_processor;
    PixelState m_state;
    APA102* m_strip;
    std::thread m_worker;
    std::mutex m_stateLock;
};

#endif /* SRC_MODULES_GREYLIGHT_H_ */
