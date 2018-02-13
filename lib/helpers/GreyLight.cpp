/*
 * GreyLight.cpp
 *
 *  Created on: Feb 5, 2018
 *      Author: Cole Brinsfield
 */

#include "GreyLight.h"
#include "lib/pixelprocessors/Gradient.h"
#include "lib/pixelprocessors/LoopModulator.h"
#include "lib/pixelprocessors/PixelChase.h"
#include "lib/pixelprocessors/Static.h"
#include "lib/pixelprocessors/TeamNumber.h"
#include "lib/pixelprocessors/Siren.h"
#include "lib/pixelprocessors/LinearScale.h"
#include "lib/pixelprocessors/CenterMirror.h"
GreyLight::GreyLight(int numLEDs) {
    state = PixelState{};
    state.fps = 60;
    state.numLEDs = numLEDs;
    state.pixels = std::vector<Color>(numLEDs);
    // processor = new LoopModulator(new Gradient({255,0,0},{0,0,255}));
    // processor = new PixelChase(
    // new LoopModulator(new Gradient({255, 0, 0}, {0, 0, 255})), {0, 100, 0});
    // processor = new TeamNumber();
    // processor =
    // new PixelChase(new Siren({255, 0, 0}, {0, 255, 0}, 3), {0, 0, 0});
    // processor = new LinearScale({255,0,0},{0,255,0},0,100, new
    // Static({0,0,0}));
    processor = new CenterMirror(
        new PixelChase(new Gradient({255, 0, 0}, {0, 0, 255}), {0, 100, 0}));
    // processor = new Gradient({255, 0, 0}, {0, 0, 255});

    worker = std::thread(&GreyLight::loop, this);
}

void GreyLight::loop() {
    //	std::cout << "beginning loop" << std::endl;

    // clock is in seconds
    // int lastTick = clock();
    //
    // while (true) {
    // 	stateLock.lock();
    //
    // 	state.frame++;
    // 	int now = clock();
    // 	state.delta = (now - lastTick) / 1000;
    // 	lastTick = now;
    // 	processor->tick(state);
    // 	writeFrame(state.pixels);
    //
    // 	stateLock.unlock();
    //
    // 	std::this_thread::sleep_for(std::chrono::milliseconds(10));
    // }
    state.frame++;
    processor->tick(state);
}

// void GreyLight::writeFrame(std::vector<Color> pixels) {
// each "pixel" has its id in front of it
// int pixelSize = sizeof(uint8_t) + sizeof(Color);
// int totalSize = pixelSize * conf::led::COUNT;
// int chunkSize = 32;
// //TODO: account for remainder from integer division
// int chunkCount = totalSize / chunkSize;
//
// int pixelIndex = 0;
// uint8_t chunk[chunkSize];
// for (int _ = 0; _ < chunkCount; _++) {
// 	for (int i = 0; i < chunkSize; i += pixelSize) {
// 		chunk[i] = pixelIndex;
// 		chunk[i + 1] = pixels.at(pixelIndex).r;
// 		chunk[i + 2] = pixels.at(pixelIndex).g;
// 		chunk[i + 3] = pixels.at(pixelIndex).b;
// 		pixelIndex++;
// 	}
// 	arduino->WriteBulk(chunk, chunkSize);
// }
// }

void GreyLight::setPixelStateProcessor(PixelStateProcessor* processor) {
    stateLock.lock();
    this->processor = processor;
    stateLock.unlock();
}
