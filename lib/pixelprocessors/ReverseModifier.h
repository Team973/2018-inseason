/*
 * ReverseModifier.h
 *
 *  Created on: March 11, 2018
 *      Author: Cole Brinsfield
 */

#ifndef SRC_MODULES_PIXELPROCESSORS_REVERSEMODIFIER_H_
#define SRC_MODULES_PIXELPROCESSORS_REVERSEMODIFIER_H_

#include "GreyLightTypes.h"
#include "PixelStateProcessor.h"
#include <vector>
#include <algorithm>

namespace LightPattern {

class ReverseModifier : public PixelStateProcessorModulator {
public:
    ReverseModifier(PixelStateProcessor* processor);
    void Tick(PixelState& state) override;
};
}
#endif /* SRC_MODULES_PIXELPROCESSORS_REVERSEMODIFIER_H_ */
