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
    g_state = PixelState{};
    g_state.fps = 60;
    g_state.numLEDs = numLEDs;
    g_state.pixels = std::vector<Color>(numLEDs);
    m_strip = new APA102(numLEDs);
    g_processor = new Static({0, 0, 0});  // start with all lights off
    m_worker = std::thread(&GreyLight::loop, this);
}

void GreyLight::loop() {
    // clock is in seconds
    int lastTick = clock();
    while (true) {
        m_stateLock.lock();
        g_state.frame++;
        int now = clock();
        g_state.delta = (now - lastTick) / 1000;
        lastTick = now;
        g_processor->tick(g_state);
        m_strip->show(g_state.pixels);
        m_stateLock.unlock();
        std::this_thread::sleep_for(
            std::chrono::milliseconds(30));  // TO-DO, fps delay math
    }
}

void GreyLight::setPixelStateProcessor(PixelStateProcessor* processor) {
    m_stateLock.lock();
    this->g_processor = processor;
    m_stateLock.unlock();
}
