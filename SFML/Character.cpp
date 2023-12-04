#include "Character.h"

Character::Character(Window& w )
	: w(w), Size(64), coordinate(sf::Vector2f(0.0f, 0.0f)), speed(sf::Vector2f(5.0f, 5.0f)) {	
}

int Character::staticFall = 1;
int Character::staticJump = 115;
int Character::getSize() {
	return Size;
}
