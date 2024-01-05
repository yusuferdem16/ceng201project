#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
class Window;

class mouseListener {
private:
	int x;
	int y;
	Window& w;
public:
	mouseListener(Window& w);
	void Listen(const sf::Event& event);
	int getX();
	int getY();
	void setX(int x);
	void setY(int y);
};



