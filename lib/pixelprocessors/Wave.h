
/*
 * Text.h
 *
 *  Created on: Mar 14, 2017
 *      Author: lytigas
 */

#ifndef SRC_MODULES_PIXELPROCESSORS_WAVE_H_
#define SRC_MODULES_PIXELPROCESSORS_WAVE_H_

#include "GreyLightTypes.h"
#include "PixelStateProcessor.h"
#include <math.h>
#include <algorithm>

namespace LightPattern {
class Wave : public PixelStateProcessor {
public:
    Wave(Color background, Color foreground, int period);
    void Tick(PixelState& state) override;

private:
    int m_period;
    Color m_background, m_foreground;
};
}

#endif /* SRC_MODULES_PIXELPROCESSORS_WAVE_H_ */
