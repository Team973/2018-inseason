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

class TeamNumber : public PixelStateProcessor {
public:
    TeamNumber();
    TeamNumber(Color foreground, Color background);
    void tick(PixelState& state);

private:
    Color foreground;
    Color background;
};

#endif /* SRC_MODULES_PIXELPROCESSORS_TEAMNUMBER_H_ */
