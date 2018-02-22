/*
 * Gradient.h
 *
 *  Created on: Feb 10, 2018
 *      Author: Cole Brinsfield
 */

#ifndef SRC_MODULES_PIXELPROCESSORS_GRADIENT_H_
#define SRC_MODULES_PIXELPROCESSORS_GRADIENT_H_

#include <vector>
#include "GreyLightTypes.h"
#include "PixelStateProcessor.h"

namespace LightPattern {

class Gradient : public PixelStateProcessor {
public:
    Gradient(Color gradientStart, Color gradientEnd);
    void Tick(PixelState& state) override;

private:
    Color m_gradientStart;
    Color m_gradientEnd;
};
}

#endif /* SRC_MODULES_PIXELPROCESSORS_GRADIENT_H_ */
