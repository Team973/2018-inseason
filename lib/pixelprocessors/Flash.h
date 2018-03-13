/*
 * Flash.h
 *
 *  Created on: Feb 10, 2018
 *      Author: Cole Brinsfield
 */

#ifndef SRC_MODULES_PIXELPROCESSORS_FLASH_H_
#define SRC_MODULES_PIXELPROCESSORS_FLASH_H_

#include "GreyLightTypes.h"
#include "PixelStateProcessor.h"
#include "lib/util/Util.h"
#include <vector>
#include <chrono>

namespace LightPattern {
class Flash : public PixelStateProcessor {
public:
    Flash(Color first, Color second, int hz, int count = -1);
    void Tick(PixelState& state) override;
    void SetColors(Color first, Color second);
    void SetFrequency(int hz);
    void Reset() override;

private:
    bool m_color = false;
    Color m_first, m_second;
    int m_hz;
    int m_count;
    int m_loopCount;
    double m_lastTime;
};
}

#endif /* SRC_MODULES_PIXELPROCESSORS_FLASH_H_ */
