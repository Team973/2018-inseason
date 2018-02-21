/*
 * PixelChase.h
 *
 *  Created on: Feb 10, 2018
 *      Author: Cole Brinsfield
 */

#ifndef SRC_MODULES_PIXELPROCESSORS_PIXELCHASE_H_
#define SRC_MODULES_PIXELPROCESSORS_PIXELCHASE_H_

#include "GreyLightTypes.h"
#include "PixelStateProcessor.h"

#include <vector>

class PixelChase : public PixelStateProcessorModulator {
public:
    PixelChase(PixelStateProcessor* processor, Color background);
    void tick(PixelState& state);

private:
    uint16_t getFrame(int n);
    Color m_background;
};

#endif /* SRC_MODULES_PIXELPROCESSORS_PIXELCHASE_H_ */
