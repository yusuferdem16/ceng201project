#include "keyListener.h"

void keyListener::Listen(const sf::Event& event) {
	//keyPressed
	if (event.type == sf::Event::KeyPressed) {
		//Example W pressed
		if (event.key.code == sf::Keyboard::W) {
			std::cout << "pressed w";
		}
	}
	if (event.type == sf::Event::KeyReleased) {

	}
}
