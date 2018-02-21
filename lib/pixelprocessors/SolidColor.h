/*
 * SolidColor.h
 *
 *  Created on: Feb 10, 2018
 *      Author: Cole Brinsfield
 */

#ifndef SRC_MODULES_PIXELPROCESSORS_SOLIDCOLOR_H_
#define SRC_MODULES_PIXELPROCESSORS_SOLIDCOLOR_H_

#include "GreyLightTypes.h"
#include "PixelStateProcessor.h"
#include <vector>

namespace LightPattern {

class SolidColor : public PixelStateProcessor {
public:
    SolidColor();
    SolidColor(Color color);
    void tick(PixelState& state);
    void setColor(Color color);

private:
    Color m_currentColor;
};
}
#endif /* SRC_MODULES_PIXELPROCESSORS_SOLIDCOLOR_H_ */
