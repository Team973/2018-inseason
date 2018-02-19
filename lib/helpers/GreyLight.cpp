/*
 * GreyLight.cpp
 * Updated version of FRC 114's HellaDees from 2017
 * Handles pixel manipulation then sends it to the APA102 interface to write
 *  Created on: Feb 5, 2018
 *      Author: Cole Brinsfield
 */

#include "GreyLight.h"
#include "lib/pixelprocessors/Static.h"
#include <iostream>

GreyLight::GreyLight(int numLEDs) {
    state = PixelState{};
    state.fps = 60;
    state.numLEDs = numLEDs;
    state.pixels = std::vector<Color>(numLEDs);
    m_strip = new APA102(numLEDs);
    processor = new Static({0, 0, 0});  // start with all lights off
    m_worker = std::thread(&GreyLight::loop, this);
}

void GreyLight::loop() {
    // clock is in seconds
    int lastTick = clock();
    while (true) {
        stateLock.lock();
        state.frame++;
        int now = clock();
        state.delta = (now - lastTick) / 1000;
        lastTick = now;
        processor->tick(state);
        m_strip->show(state.pixels);
        stateLock.unlock();
        std::this_thread::sleep_for(
            std::chrono::milliseconds(30));  // TO-DO, fps delay math
    }
}

void GreyLight::setPixelStateProcessor(PixelStateProcessor* processor) {
    stateLock.lock();
    this->processor = processor;
    stateLock.unlock();
}
