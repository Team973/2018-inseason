/*
 * PixelChase.h
 * Creates an "inch-worm" of pixels moving from one side to the other of the
 * strip Created on: Feb 10, 2018 Author: Cole Brinsfield
 */

#ifndef SRC_MODULES_PIXELPROCESSORS_PIXELCHASE_H_
#define SRC_MODULES_PIXELPROCESSORS_PIXELCHASE_H_

#include "GreyLightTypes.h"
#include "PixelStateProcessor.h"
#include <vector>

namespace LightPattern {

class PixelChase : public PixelStateProcessorModulator {
public:
    PixelChase(PixelStateProcessor* processor, Color background);
    void tick(PixelState& state);

private:
    uint16_t getFrame(int n);
    Color m_background;
};
}

#endif /* SRC_MODULES_PIXELPROCESSORS_PIXELCHASE_H_ */
