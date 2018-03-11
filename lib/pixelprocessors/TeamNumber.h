/*
 * TeamNumber.h
 *
 *  Created on: Feb 8, 2018
 *      Author: Cole Brinsfield
 */

#ifndef SRC_MODULES_PIXELPROCESSORS_TEAMNUMBER_H_
#define SRC_MODULES_PIXELPROCESSORS_TEAMNUMBER_H_

#include "GreyLightTypes.h"
#include "PixelStateProcessor.h"

namespace LightPattern {
class TeamNumber : public PixelStateProcessor {
public:
    TeamNumber();
    TeamNumber(Color foreground, Color background);
    void Tick(PixelState& state) override;

private:
    Color m_foreground;
    Color m_background;
};
}

#endif /* SRC_MODULES_PIXELPROCESSORS_TEAMNUMBER_H_ */