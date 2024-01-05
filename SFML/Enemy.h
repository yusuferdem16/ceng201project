#pragma once
#include <thread>
#include <SFML/System/Vector2.hpp>
class Enemy {
	private:
		int health;
		sf::Vector2f speed;
		sf::Vector2f coordinate;
		int damage;
};
