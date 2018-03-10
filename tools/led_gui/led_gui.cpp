#include <SFML/Graphics.hpp>
#include "lib/helpers/GreyLight.h"
#include "lib/pixelprocessors/LinearScale.h"
#include "lib/pixelprocessors/SolidColor.h"
#include "lib/pixelprocessors/Flash.h"

#include <stdio.h>
#include <iostream>
#include <time.h>
#include <sstream>

const int LEDRadius = 15;

sf::CircleShape* createCircles(int num = 224) {
    int diameter = LEDRadius * 2;
    sf::CircleShape* LEDs = new sf::CircleShape[num];
    for (int i = 0; i < num; i++) {
        LEDs[i] = sf::CircleShape(LEDRadius);
        LEDs[i].setFillColor(sf::Color::White);
        LEDs[i].setPosition(i * diameter, 0);
    }
    return LEDs;
}

void updateAndDraw(std::vector<Color> v, sf::RenderWindow& window,
                   sf::CircleShape* disp, unsigned int num = 224) {
    window.clear(sf::Color(200, 200, 200));
    for (unsigned int i = 0; i < num; i++) {
        disp[i].setFillColor(sf::Color(v.at(i).r, v.at(i).g, v.at(i).b, 255));
        window.draw(disp[i]);
    }
    window.display();
}

int main(int argc, char* argv[]) {
    if (argc == 1) {
        std::cerr << "\033[1;31mNumber of LEDs must be passed as an "
                     "argument!\033[0m\n";
        return -1;
    }
    std::istringstream ss(argv[1]);
    int numLEDs;
    if (!(ss >> numLEDs))
        std::cerr << "Invalid number " << argv[1] << '\n';
    GreyLight* led = new GreyLight(numLEDs);
    struct timespec tim, tim2;
    tim.tv_sec = 0;
    tim.tv_nsec = 50 * 1000000;  // the first number represents ms
    sf::RenderWindow window(
        sf::VideoMode(numLEDs * LEDRadius * 2, LEDRadius * 2),
        "LED Simulator");  // Window with label 'LED Simulator',
                           // x=numLed*diameter, y=diameter
    sf::CircleShape* LEDs = createCircles(numLEDs);
    Flash *flash = new Flash({0,255,0},{0,0,0},50,15);
    SolidColor *solid = new SolidColor({255,0,0});
    led->SetPixelStateProcessor(flash);
    int count = 1;
    int state = 0;
    while (window.isOpen()) {
        std::cout<<"count: "<<count<<" state: "<<state<<std::endl;
        if(count++%50==0){
          state++;
        }
        if(state==0){

        }
        if(state==1){
          solid->SetColor({255,0,0});
          led->SetPixelStateProcessor(solid);
        }
        if(state==2){
          solid->SetColor({0,0,0});
        }
        if(state==3){
          led->SetPixelStateProcessor(flash);
          state=0;
        }
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        led->Loop();
        updateAndDraw(led->GetState().pixels, window, LEDs, numLEDs);
        nanosleep(&tim, &tim2);
    }

    return 0;
}
