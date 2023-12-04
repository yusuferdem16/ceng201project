#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "mouseListener.h"
#include "keyListener.h"
#include "ImageIcons.h"
#include "World.h"
#include "Character.h"
#include "Sounds.h"

#include "Level.h"

class mouseListener;
class keyListener;
class ImageIcons;
class World;
class Character;
class Level;

class Window {
private:
	Level level;
	World myWorld;
	sf::RenderWindow window;
	mouseListener mListener;
	keyListener kListener;
	ImageIcons myIcons;
	Character myCharacter;
	sf::View view;
public:	
	//in constructor first define myWorld after window because we are using numbers from World class.
	Window(Level level);
	void run();
	void implementation();
	void drawGraphics();
	void drawWorld();
	void drawCharacter();
	void leftCollisions();
	void rightCollisions();
	void upCollisions();
	void bottomCollisions();
};


