/*
 * Gradient.h
 *
 *  Created on: Feb 10, 2018
 *      Author: Cole Brinsfield
 */

#ifndef SRC_MODULES_PIXELPROCESSORS_GRADIENT_H_
#define SRC_MODULES_PIXELPROCESSORS_GRADIENT_H_

#include <vector>

// #include "Settings.h"
#include "GreyLightTypes.h"
#include "PixelStateProcessor.h"
#include <iostream>

class Gradient : public PixelStateProcessor {
public:
    Gradient(Color gradientStart, Color gradientEnd);
    void tick(PixelState& state);

private:
    Color m_gradientStart;
    Color m_gradientEnd;
};

#endif /* SRC_MODULES_PIXELPROCESSORS_GRADIENT_H_ */
