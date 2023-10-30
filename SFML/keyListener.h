#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>
class Window;

class keyListener {
private:
	Window& w;

public:
	keyListener(Window& w) : w(w) {} //implemented constructor
	void Listen(const sf::Event& event);
};
