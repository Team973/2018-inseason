/*
 * LengthModifier.h
 *
 *  Created on: March 11, 2018
 *      Author: Cole Brinsfield
 */

#ifndef SRC_MODULES_PIXELPROCESSORS_LENGTHMODIFIER_H_
#define SRC_MODULES_PIXELPROCESSORS_LENGTHMODIFIER_H_

#include "GreyLightTypes.h"
#include "PixelStateProcessor.h"
#include <vector>

namespace LightPattern {

class LengthModifier : public PixelStateProcessorModulator {
public:
    LengthModifier(PixelStateProcessor* processor, int numLEDs);
    void Tick(PixelState& state) override;

private:
    int m_numLEDS;
};
}
#endif /* SRC_MODULES_PIXELPROCESSORS_LENGTHMODIFIER_H_ */
