/*
 * GreyLight.cpp
 * Updated version of FRC 114's HellaDees from 2017
 * Handles pixel manipulation then sends it to the APA102 interface to write
 *  Created on: Feb 5, 2018
 *      Author: Cole Brinsfield
 */

#include "GreyLight.h"
#include "lib/pixelprocessors/SolidColor.h"
#include <iostream>

using namespace GreyLightType;

GreyLight::GreyLight(int numLEDs) {
    m_state = PixelState{};
    m_state.fps = 60;
    m_state.numLEDs = numLEDs;
    m_state.pixels = std::vector<Color>(numLEDs);
    m_strip = new APA102(numLEDs);
    m_processor = new SolidColor({0, 0, 0});  // start with all lights off
    m_worker = std::thread(&GreyLight::Loop, this);
}

void GreyLight::Loop() {
    // clock is in seconds
    int lastTick = clock();
    while (true) {
        m_stateLock.lock();
        m_state.frame++;
        int now = clock();
        m_state.delta = (now - lastTick) / 1000;
        lastTick = now;
        m_processor->tick(m_state);
        m_strip->Show(m_state.pixels);
        m_stateLock.unlock();
        std::this_thread::sleep_for(
            std::chrono::milliseconds(30));  // TO-DO, fps delay math
    }
}

void GreyLight::SetPixelStateProcessor(PixelStateProcessor* processor) {
    m_stateLock.lock();
    this->m_processor = processor;
    m_stateLock.unlock();
}
