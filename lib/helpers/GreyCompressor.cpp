/*
 * GreyCompressor.cpp
 *
 *  Created on: Nov 3, 2015
 *      Author: Andrew
 */

#include "GreyCompressor.h"

#include "WPILib.h"
#include "lib/filters/Debouncer.h"

namespace frc973 {

GreyCompressor::GreyCompressor(DigitalInput *pressureSwitch, Relay *compressor,
                               TaskMgr *scheduler)
        : m_enabled(true)
        , m_airPressureSwitch(pressureSwitch)
        , m_compressor(compressor)
        , m_scheduler(scheduler) {
    this->m_scheduler->RegisterTask("Compressor", this, TASK_PERIODIC);
}

GreyCompressor::~GreyCompressor() {
    this->m_scheduler->UnregisterTask(this);
}

void GreyCompressor::Enable() {
    m_enabled = true;
}

void GreyCompressor::Disable() {
    m_enabled = false;
}

void GreyCompressor::TaskPeriodic(RobotMode mode) {
    printf("Pressure: %d\n", m_airPressureSwitch->Get());
    if (!m_airPressureSwitch->Get() && m_enabled) {
        m_compressor->Set(Relay::kForward);
        printf("Enabled\n");
    }
    else {
        m_compressor->Set(Relay::kOff);
        printf("Disabled\n");
    }
}
}
