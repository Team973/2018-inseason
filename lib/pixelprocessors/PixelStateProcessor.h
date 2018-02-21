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
    virtual void tick(PixelState& state) = 0;
    // empty virtual to stop compiler warnings
};

class PixelStateProcessorModulator : public PixelStateProcessor {
public:
    void tick(PixelState& state) {
        this->processor->tick(state);
    }

    void setProcessor(PixelStateProcessor* processor) {
        this->processor = processor;
    }
    PixelStateProcessor* processor;
};
}

#endif /* SRC_MODULES_PIXELSTATEPROCESSOR_H_ */
