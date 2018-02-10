#include <SFML/Graphics.hpp>


#include "lib/helpers/GreyLight.h"

#include <stdio.h>
#include <iostream>
#include <time.h>
#include <sstream>



sf::CircleShape* createCircles(int num=224) {
	int radius = 15;
	int xpos = 0;
	int ypos = 0;
	int scalefactor = radius*2;

	sf::CircleShape* v = new sf::CircleShape[num];
	for (int i = 0; i < num; i++) {
		v[i] = sf::CircleShape(radius);
		v[i].setFillColor(sf::Color::White);


		xpos=i;
		//pick our ypos
		ypos=0;

		v[i].setPosition(xpos*scalefactor, ypos*scalefactor);
	}
	return v;
}

void updateAndDraw(std::vector<Color> v, sf::RenderWindow& window, sf::CircleShape* disp, unsigned int num=224) {
	window.clear(sf::Color(200,200,200));

	//update the colors
	for (unsigned int i = 0; i < num; i++) {
		disp[i].setFillColor(sf::Color(v.at(i).r, v.at(i).g, v.at(i).b, 255));
		window.draw(disp[i]);
	}

	window.display();
}


int main(int argc, char *argv[]) {
	if(argc==1){
		std::cerr << "\033[1;31mNumber of LEDs must be passed as an argument!" << "\033[0m\n";
		return -1;
	}
	std::istringstream ss(argv[1]);
	int numLEDs;
	if (!(ss >> numLEDs))
		std::cerr << "Invalid number " << argv[1] << '\n';
	GreyLight* led = new GreyLight(numLEDs);

	struct timespec tim, tim2;
	tim.tv_sec = 0;
	tim.tv_nsec = 50*1000000; //the first number represents ms

    sf::RenderWindow window(sf::VideoMode(numLEDs*15*2,15*2), "LED Simulator");
    sf::CircleShape* v = createCircles(numLEDs);


    led->loop();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        led->loop();
        updateAndDraw(led->state.pixels, window, v, numLEDs);
        nanosleep(&tim,&tim2);
    }

    return 0;
}
