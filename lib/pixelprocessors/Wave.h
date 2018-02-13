
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

class Wave : public PixelStateProcessor {
public:
    Wave(Color background, Color foreground, int period);
    void tick(PixelState& state);
    int period;

private:
    Color background, foreground;
    double offset;
};

#endif /* SRC_MODULES_PIXELPROCESSORS_WAVE_H_ */
