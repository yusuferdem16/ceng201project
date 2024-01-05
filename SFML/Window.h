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
#include "Chronometer.h"
class mouseListener;
class keyListener;
class ImageIcons;
class World;
class Character;
class Sounds;
class Level;
class Chronometer;

class Window {
private:
	Level level;
	World myWorld;
	sf::RenderWindow window;
	mouseListener mListener;
	keyListener kListener;
	ImageIcons myIcons;
	Character myCharacter;
	sf::Text startText;
	sf::Text displayScoresText;
	sf::Text continueText;
	sf::Text quitLevelText;
	sf::Text pauseText;
	sf::Text exitText;
	sf::Font font;
	bool inMainMenu;
	bool inGame;
	bool inPauseMenu;
	bool inDisplayScoresMenu;
	bool inLevelOverScreen;
	bool inGameOverScreen;
	bool checkSpike;
	bool checkLava;
	bool checkLadder;
	Sounds sounds;
	Chronometer gameClock;
	Chronometer lavaClock;
	sf::Time gameTimeLimit;
	sf::View view;
	float dt;
	int score;
	int timesGotHit;
	sf::Vector2f endPosition;
	int lavatimer;

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
	void handleMainMenuInput();
	void drawMainMenu();
	void enterGameState();
	void initializeMainMenu();
	void drawDisplayScores();
	void drawPauseMenu();
	void handlePauseMenuInput();
	void drawGameOverScreen();
	void drawLevelOverScreen();
	void resetGameState();
	void checkEndState();
	void calculateScore();
	int getTimesGotHit();
	int getScore();
	void setTimesGotHit(int timesGotHit);
	void setScore(int score);
};


