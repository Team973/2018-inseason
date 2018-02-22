/*
 * CenterMirror.h
 *
 *  Created on: Feb 10, 2018
 *      Author: Cole Brinsfield
 */

#ifndef SRC_MODULES_PIXELPROCESSORS_CENTERMIRROR_H_
#define SRC_MODULES_PIXELPROCESSORS_CENTERMIRROR_H_

#include <vector>
#include <algorithm>
#include "GreyLightTypes.h"
#include "PixelStateProcessor.h"

namespace LightPattern {

class CenterMirror : public PixelStateProcessorModulator {
public:
    CenterMirror(PixelStateProcessor* processor, bool inverse = false);
    void Tick(PixelState& state);

private:
    void PushToRightSide(PixelState& state);
    bool m_inverse;
    uint8_t m_previousNumLEDs;
};
}
#endif /* SRC_MODULES_PIXELPROCESSORS_CENTERMIRROR_H_ */
