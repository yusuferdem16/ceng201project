#pragma once
#include <SFML/System/Vector2.hpp>
#include "ImageIcons.h"
class Window;

class Character {
private:
	const int Size;
	Window& w;

public:
	Character(Window& w);
	sf::Vector2f coordinate;
	sf::Vector2f speed;
	int getSize();

	static int staticFall;
	static int staticJump;
	bool jumping = false;
	bool falling = false;
	bool canGoLeft = true;
	bool canGoRight = true;
	bool canGoUp = true;
	bool canGoDown = true;

};

