/*
 * AutoIndicator.cpp
 *
 *  Created on: March 11, 2018
 *      Author: Cole Brinsfield
 */

#include "AutoIndicator.h"
#include <iostream>
namespace LightPattern {
AutoIndicator::AutoIndicator() {
    m_gameData = "";
}
void AutoIndicator::SetData(std::string gameDataStr) {
    m_gameData = gameDataStr;
}

void AutoIndicator::Tick(PixelState& state) {
    int column_width = state.numLEDs / 3;
    if (m_gameData.size() == 3) {
        switch (m_gameData[0]) {
            case 'L':
                std::fill(state.pixels.begin(),
                          state.pixels.end() - column_width * 2,
                          Color{255, 0, 255});
                break;
            case 'R':
                std::fill(state.pixels.begin(),
                          state.pixels.end() - column_width * 2,
                          Color{255, 255, 255});
                break;
            default:
                std::fill(state.pixels.begin(),
                          state.pixels.end() - column_width * 2,
                          Color{255, 0, 0});
        }
        switch (m_gameData[1]) {
            case 'L':
                std::fill(state.pixels.begin() + column_width,
                          state.pixels.end() - column_width,
                          Color{255, 0, 255});
                break;
            case 'R':
                std::fill(state.pixels.begin() + column_width,
                          state.pixels.end() - column_width,
                          Color{255, 255, 255});
                break;
            default:
                std::fill(state.pixels.begin() + column_width,
                          state.pixels.end() - column_width, Color{255, 0, 0});
        }
        switch (m_gameData[2]) {
            case 'L':
                std::fill(state.pixels.begin() + column_width * 2,
                          state.pixels.end(), Color{255, 0, 255});
                break;
            case 'R':
                std::fill(state.pixels.begin() + column_width * 2,
                          state.pixels.end(), Color{255, 255, 255});
                break;
            default:
                std::fill(state.pixels.begin() + column_width * 2,
                          state.pixels.end(), Color{255, 0, 0});
        }
    }
    else {
        std::fill(state.pixels.begin(), state.pixels.end(), Color{255, 255, 0});
    }
}
}
