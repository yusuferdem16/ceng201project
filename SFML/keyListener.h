#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>
class Window;

class keyListener {
private:
	bool aPressed;
	bool sPressed;
	bool dPressed;
	Window& w;
public:
	bool wPressed;
	keyListener(Window& w);
	void Listen(const sf::Event& event);
	bool isWPressed();
	bool isAPressed();
	bool isSPressed();
	bool isDPressed();
	void resetState();

};

