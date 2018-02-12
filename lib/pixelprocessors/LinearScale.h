/*
 * Speedometer.h
 *
 *  Created on: Mar 30, 2017
 *      Author: Cole
 */
#include "GreyLightTypes.h"
#include "PixelStateProcessor.h"

#ifndef SRC_MODULES_PIXELPROCESSORS_LINEARSCALE_H_
#define SRC_MODULES_PIXELPROCESSORS_LINEARSCALE_H_

class LinearScale : public PixelStateProcessorModulator {
public:
    LinearScale(Color minColor, Color maxColor, double minVal, double maxVal,
                PixelStateProcessor* modulator);
    void tick(PixelState& state);
    void updateValue(double value);

private:
    Color minColor;
    Color maxColor;
    double minVal, maxVal, currentValue;
};

#endif /* SRC_MODULES_PIXELPROCESSORS_LINEARSCALE_H_ */
