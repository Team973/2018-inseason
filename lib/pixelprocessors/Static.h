/*
 * Static.h
 *
 *  Created on: Feb 10, 2018
 *      Author: Cole Brinsfield
 */

#ifndef SRC_MODULES_PIXELPROCESSORS_STATIC_H_
#define SRC_MODULES_PIXELPROCESSORS_STATIC_H_

#include "GreyLightTypes.h"
#include "PixelStateProcessor.h"

#include <vector>

class Static : public PixelStateProcessor {
public:
    Static();
    Static(Color color);
    void tick(PixelState& state);
    void setColor(Color color);

private:
    Color currentColor;
};

#endif /* SRC_MODULES_PIXELPROCESSORS_STATIC_H_ */
