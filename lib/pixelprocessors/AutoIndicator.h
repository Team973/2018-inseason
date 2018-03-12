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
