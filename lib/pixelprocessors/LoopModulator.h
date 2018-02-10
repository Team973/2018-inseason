/*
 * LoopModulator.h
 *
 *  Created on: Feb 10, 2018
 *      Author: Cole Brinsfield
 */

#ifndef SRC_MODULES_PIXELPROCESSORS_LOOPMODULATOR_H_
#define SRC_MODULES_PIXELPROCESSORS_LOOPMODULATOR_H_

#include <vector>

#include "GreyLightTypes.h"
#include "PixelStateProcessor.h"

class LoopModulator : public PixelStateProcessorModulator {
public:
    LoopModulator(PixelStateProcessor* processor);
    void tick(PixelState& state);

private:
    void rotate(std::vector<Color>& pixels, int amount, int numLEDs);
};

#endif /* SRC_MODULES_PIXELPROCESSORS_LOOPMODULATOR_H_ */
