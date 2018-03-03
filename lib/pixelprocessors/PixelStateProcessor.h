/*
 * PixelStateProcessor.h
 *
 *  Created on: Feb 5, 2018
 *      Author: Cole Brinsfield
 */
#ifndef SRC_MODULES_PIXELSTATEPROCESSOR_H_
#define SRC_MODULES_PIXELSTATEPROCESSOR_H_

#include <vector>
#include "GreyLightTypes.h"

using namespace GreyLightType;
namespace LightPattern {

class PixelStateProcessor {
public:
    virtual void Tick(PixelState& state) = 0;
    virtual void Reset() = 0;
    // empty virtual to stop compiler warnings
};

class PixelStateProcessorModulator : public PixelStateProcessor {
public:
    void Tick(PixelState& state) {
        this->processor->Tick(state);
    }

    void SetProcessor(PixelStateProcessor* processor) {
        this->processor = processor;
    }

    void Reset() {
        this->processor->Reset();
    }
    PixelStateProcessor* processor;
};
}

#endif /* SRC_MODULES_PIXELSTATEPROCESSOR_H_ */
