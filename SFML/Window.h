#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "mouseListener.h"
#include "keyListener.h"
#include "ImageIcons.h"
class mouseListener;
class keyListener;
class ImageIcons;

class Window {
private:
	sf::RenderWindow window;
	sf::CircleShape shape;
	mouseListener mListener;
	keyListener kListener;
	ImageIcons myIcons;
public:

	Window() : window(sf::VideoMode(800, 800), ""), shape(100.f)
		, mListener(*this), kListener(*this), myIcons(*this) {}
	void run();
	void implementation();
	void drawGraphics();
	void start();
	int getX();
	int getY();
};

