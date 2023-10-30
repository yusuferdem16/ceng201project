#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "mouseListener.h"
#include "keyListener.h"
class mouseListener;
class keyListener;

class Window {
private:
	sf::RenderWindow window;
	sf::CircleShape shape;
	mouseListener mListener;
	keyListener kListener;
public:

	Window() : window(sf::VideoMode(800, 800), ""), shape(100.f), mListener(*this), kListener(*this) {}
	void run();
	void implementation();
	void drawGraphics();
	void start();
	int getX();
	int getY();
};

