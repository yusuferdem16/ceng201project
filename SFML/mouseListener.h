#ifndef MOUSELISTENER_H
#define MOUSELISTENER_H

#include <SFML/Graphics.hpp>
#include "Window.h"
#include <iostream>

class mouseListener {
private:
	int x;
	int y;
	Window& w;
	Window defaultWindow;
public:
	mouseListener();
	mouseListener(Window& w);
	void Listen(const sf::Event& event);
	int getX();
	int getY();
	void setX(int x);
	void setY(int y);
};
#endif


