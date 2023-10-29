#ifndef WINDOW
#define WINDOW

#include <iostream>
#include <SFML/Graphics.hpp>
#include "mouseListener.h"

class Window {
private:
	int x;
	int y;
	sf::RenderWindow window;
	sf::CircleShape shape;
	mouseListener mListener;
public:
	Window();
	void run();
	void implementation();
	void drawGraphics();
	void keyListener(const sf::Event& e);
	void start();
};
#endif

