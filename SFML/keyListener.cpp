#include "keyListener.h"

keyListener::keyListener(Window& w) : w(w), wPressed(false), aPressed(false)
, sPressed(false), dPressed(false) {}


void keyListener::Listen(const sf::Event& event) {
	//keyPressed

	if (event.type == sf::Event::KeyPressed) {
		// A pressed
		if (event.key.code == sf::Keyboard::A) {
			aPressed = true;
		}
		// D pressed
		if (event.key.code == sf::Keyboard::D) {
			dPressed = true;

		}
		// S pressed
		if (event.key.code == sf::Keyboard::S) {
			sPressed = true;

		}
		// W pressed
		if (event.key.code == sf::Keyboard::W) {
			wPressed = true;
		}
	}
	//keyReleased
	if (event.type == sf::Event::KeyReleased) {
		// A released
		if (event.key.code == sf::Keyboard::A) {
			aPressed = false;
		}
		// D released
		if (event.key.code == sf::Keyboard::D) {
			dPressed = false;
		}
		// S released
		if (event.key.code == sf::Keyboard::S) {
			sPressed = false;
		}
	}
}


bool keyListener::isWPressed() {
	return wPressed;
}

bool keyListener::isAPressed() {
	return aPressed;
}

bool keyListener::isSPressed() {
	return sPressed;
}

bool keyListener::isDPressed()
{
	return dPressed;
}

void keyListener::resetState() {
	wPressed = false;
	aPressed = false;
	sPressed = false;
	dPressed = false;
}







