/*
 * AutoIndicator.h
 *
 *  Created on: Feb 10, 2018
 *      Author: Cole Brinsfield
 */

#ifndef SRC_MODULES_PIXELPROCESSORS_AUTOINDICATOR_H_
#define SRC_MODULES_PIXELPROCESSORS_AUTOINDICATOR_H_

#include "GreyLightTypes.h"
#include "PixelStateProcessor.h"
#include <vector>
#include <string>

namespace LightPattern {
static constexpr Color LEFT_GREEN = {0, 255, 0};
static constexpr Color RIGHT_WHITE = {255, 255, 255};
static constexpr Color NO_MESSAGE_BLUE = {0, 0, 255};
static constexpr Color DEFAULT_FILL_RED = {255, 0, 0};

class AutoIndicator : public PixelStateProcessor {
public:
    AutoIndicator();
    void Tick(PixelState& state) override;
    void SetData(std::string gameDataStr);

private:
    std::string m_gameData;
};
}
#endif /* SRC_MODULES_PIXELPROCESSORS_AUTOINDICATOR_H_ */
