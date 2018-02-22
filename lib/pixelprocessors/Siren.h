/*
 * Siren.h
 *
 *  Created on: Feb 10, 2018
 *      Author: Cole Brinsfield
 */

#ifndef SRC_MODULES_PIXELPROCESSORS_SIREN_H_
#define SRC_MODULES_PIXELPROCESSORS_SIREN_H_

#include "GreyLightTypes.h"
#include "PixelStateProcessor.h"
#include <vector>

namespace LightPattern {
class Siren : public PixelStateProcessor {
public:
    Siren(Color first, Color second, int frameDuration = 4);
    void Tick(PixelState& state) override;
    void SetColors(Color first, Color second);
    void SetFrameDuration(int frameDuration);

private:
    bool m_color = false;
    Color m_first, m_second;
    int m_frameDuration;
};
}

#endif /* SRC_MODULES_PIXELPROCESSORS_SIREN_H_ */
