#include "Window.h"

Window::Window(Level level) : level(level), myWorld(level.world),
mListener(*this), kListener(*this), myIcons(*this), myCharacter(*this), sounds(*this)
, window(sf::VideoMode(20 * 64
	, 10 * 64), ""),
	view(sf::Vector2f(0.0f, 0.0f),
		sf::Vector2f(20 * 64
			, 10 * 64)), inMainMenu(true), inDisplayScoresMenu(false), inGame(false), inPauseMenu(false), inGameOverScreen(false), inLevelOverScreen(false),
	gameTimeLimit(sf::seconds(120)), score(0), timesGotHit(0),
	lavatimer(0) {
	initializeMainMenu();
	gameClock.reset();
	lavaClock.reset();
}


void Window::run() {

	implementation();

	while (window.isOpen())
	{
		if (inMainMenu) {
			handleMainMenuInput();
			drawMainMenu();
		}
		else if (inGame) {
			enterGameState();
		}
		else if (inPauseMenu) {
			handlePauseMenuInput();
			drawPauseMenu();
		}
		else if (inDisplayScoresMenu) {
			drawDisplayScores();
		}
		else if (inLevelOverScreen) {
			drawLevelOverScreen();
		}
		else if (inGameOverScreen) {
			drawGameOverScreen();
		}
	}
}

void Window::initializeMainMenu() {
	if (!font.loadFromFile("Arial.ttf")) {
		// Handle font loading error
	}
	startText.setFont(font);
	startText.setString("Start Game");
	startText.setCharacterSize(30);
	sf::FloatRect startTextRect = startText.getLocalBounds();
	startText.setOrigin(startTextRect.left + startTextRect.width / 2.0f,
		startTextRect.top + startTextRect.height / 2.0f);
	startText.setPosition(sf::Vector2f(window.getView().getCenter().x, window.getView().getCenter().y - 100.0f));

	// Initialize exitText
	exitText.setFont(font);
	exitText.setString("Exit Game");
	exitText.setCharacterSize(30);
	sf::FloatRect exitTextRect = exitText.getLocalBounds();
	exitText.setOrigin(exitTextRect.left + exitTextRect.width / 2.0f,
		exitTextRect.top + exitTextRect.height / 2.0f);
	exitText.setPosition(sf::Vector2f(window.getView().getCenter().x, window.getView().getCenter().y - 25.0f));

	//Initialize displayScoresText
	displayScoresText.setFont(font);
	displayScoresText.setString("Display Scores");
	displayScoresText.setCharacterSize(30);
	sf::FloatRect displayScoresRect = displayScoresText.getLocalBounds();
	displayScoresText.setOrigin(displayScoresRect.left + displayScoresRect.width / 2.0f,
		displayScoresRect.top + displayScoresRect.height / 2.0f);
	displayScoresText.setPosition(sf::Vector2f(window.getView().getCenter().x, window.getView().getCenter().y + 50.0f));
}

void Window::enterGameState() {
	sf::Event event;
	while (window.pollEvent(event)) {
		sf::Time elapsedTime = gameClock.getElapsedTime();
		sf::Time remainingTime = gameTimeLimit - elapsedTime;
		calculateScore();
		if (event.type == sf::Event::Closed) {
			window.close();
		}
		else if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Escape) {
				// Toggle the pause menu only when inside the game
				if (!inPauseMenu) {
					inPauseMenu = true;
					inGame = false;
					inMainMenu = false;
				}
			}
			if (inPauseMenu) {
				gameClock.pause();
			}
			else {
				gameClock.resume();
			}
		}
		else if (event.type == sf::Event::Resized) {
			// Update the view to maintain the aspect ratio
			float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
			view.setSize(20 * 64 * aspectRatio, 10 * 64);
			window.setView(view);
		}

		mListener.Listen(event);
		kListener.Listen(event);
		checkEndState();
	}
	drawGraphics();
}


void Window::drawMainMenu() {
	window.clear();

	// Draw main menu options
	window.draw(startText);
	window.draw(displayScoresText);
	window.draw(exitText);

	window.display();
}

void Window::handleMainMenuInput() {
	sf::Event event;
	gameClock.reset();
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
		}
		else if (event.type == sf::Event::MouseButtonPressed) {
			sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
			if (startText.getGlobalBounds().contains(mousePos)) {
				inGame = true;
				inMainMenu = false;
				inPauseMenu = false;
			}
			else if (exitText.getGlobalBounds().contains(mousePos)) {
				window.close();
			}
		}
	}
}

void Window::drawPauseMenu() {
	window.clear();

	continueText.setFont(font);
	continueText.setString("Continue");
	continueText.setCharacterSize(30);
	sf::FloatRect continueTextRect = continueText.getLocalBounds();
	continueText.setOrigin(continueTextRect.left + continueTextRect.width / 2.0f,
		continueTextRect.top + continueTextRect.height / 2.0f);
	continueText.setPosition(sf::Vector2f(window.getView().getCenter().x, window.getView().getCenter().y - 100.0f));

	// Initialize quit level text
	quitLevelText.setFont(font);
	quitLevelText.setString("Quit Level");
	quitLevelText.setCharacterSize(30);
	sf::FloatRect quitLevelTextRect = quitLevelText.getLocalBounds();
	quitLevelText.setOrigin(quitLevelTextRect.left + quitLevelTextRect.width / 2.0f,
		quitLevelTextRect.top + quitLevelTextRect.height / 2.0f);
	quitLevelText.setPosition(sf::Vector2f(window.getView().getCenter().x, window.getView().getCenter().y - 25.0f));

	window.draw(continueText);
	window.draw(quitLevelText);
	window.display();
}

void Window::handlePauseMenuInput() {
	sf::Event event;
	if (!myCharacter.jumping || !myCharacter.falling) {
		kListener.resetState();
	}
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
		}
		else if (event.type == sf::Event::MouseButtonPressed) {
			sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
			if (continueText.getGlobalBounds().contains(mousePos)) {
				inGame = true;
				inPauseMenu = false;
				inMainMenu = false;

			}
			else if (quitLevelText.getGlobalBounds().contains(mousePos)) {
				resetGameState();
				inPauseMenu = false;
				inGame = false;
				inMainMenu = true;
				setScore(0);
				setTimesGotHit(0);
				gameClock.reset();
			}
		}


	}
}

void Window::drawLevelOverScreen() {
	window.clear();

	sf::Text levelCompleteText;
	levelCompleteText.setFont(font);
	levelCompleteText.setString("Level Complete!\nScore: " + std::to_string(score) + "\nTimes Got Hit: " + std::to_string(getTimesGotHit()));
	levelCompleteText.setCharacterSize(30);
	levelCompleteText.setFillColor(sf::Color::Green);
	levelCompleteText.setPosition(view.getCenter().x - 150, view.getCenter().y - 50);

	window.draw(levelCompleteText);

	window.display();
	//this->sounds.soundLibrary[4].play();
	// Display score information for 5 seconds 
	sf::sleep(sf::seconds(5.0));

	// Reset game state and return to main menu
	inLevelOverScreen = false;
	inMainMenu = true;
	setScore(0);
	resetGameState();
	setTimesGotHit(0);
	gameClock.reset();
	drawMainMenu();
}

void Window::drawGameOverScreen() {
	window.clear();


	sf::Text gameOverText;
	gameOverText.setFont(font);
	gameOverText.setString("Game over...\nScore: " + std::to_string(score) + "\nTimes Got Hit: " + std::to_string(getTimesGotHit()));
	gameOverText.setCharacterSize(40);
	gameOverText.setFillColor(sf::Color::Red);  // Set color to red because red == failure
	gameOverText.setPosition(view.getCenter().x - 100, view.getCenter().y - 50);

	window.draw(gameOverText);

	window.display();
	//this->sounds.soundLibrary[5].play();
	// Add a delay of 5 seconds
	sf::sleep(sf::seconds(5.0));

	// Reset game state and return to main menu
	inGameOverScreen = false;
	inMainMenu = true;
	setScore(0);
	resetGameState();
	setTimesGotHit(0);
	gameClock.reset();
	drawMainMenu();
	myCharacter.coordinate = sf::Vector2f(0.0f, 0.0f);  // Reset character position
	view.setCenter(sf::Vector2f(20 * 64 / 2, 10 * 64 / 2));  // Reset view position
}


int Window::getScore() {
	return this->score;
}

void Window::setScore(int score) {
	this->score = score;
}

int Window::getTimesGotHit() {
	return this->timesGotHit;
}

void Window::setTimesGotHit(int timesGotHit) {
	this->timesGotHit = timesGotHit;
}


void Window::calculateScore() {
	setScore((gameTimeLimit.asSeconds() - gameClock.getElapsedTime().asSeconds()) * 5 - (getTimesGotHit() * 50));
}

void Window::implementation() {
	window.setFramerateLimit(60);
}
//Empty for now
void Window::drawDisplayScores() {

}

void Window::resetGameState() {
	window.setView(view);
	this->timesGotHit++;
}



void Window::drawGraphics() {
	sf::Time time = gameClock.getElapsedTime();
	window.clear(sf::Color(255, 255, 255));

	/*window.draw(myIcons.allSprites[0]);
	 0 th element is character_64.png at this point.
	we can use a for loop for every sprite when we need*/

	window.clear();

	//Character is on left
	if (myCharacter.coordinate.x < 10 * 64 - 32) {
		view.setCenter(sf::Vector2f(20 * 64 / 2, 10 * 64 / 2));
	}
	//Character is on right
	else if (myCharacter.coordinate.x > myWorld.getHorizontalBlockNumber() * myWorld.getTileSize() - 10 * 64 - 32) {
		view.setCenter(sf::Vector2f(myWorld.getHorizontalBlockNumber() * myWorld.getTileSize() - 10 * 64, 10 * 64 / 2));
	}
	//Window is sliding
	else {
		view.setCenter(sf::Vector2f(myCharacter.coordinate.x + 32, 10 * 64 / 2));
	}

	window.setView(view);
	drawWorld();
	drawCharacter();

	//Timer text
	sf::Text timerText;
	timerText.setFont(font);
	timerText.setCharacterSize(20);
	timerText.setFillColor(sf::Color::White);


	//Score text
	sf::Text scoreText;
	scoreText.setFont(font);
	scoreText.setCharacterSize(20);
	scoreText.setFillColor(sf::Color::White);

	//Times got hit text
	sf::Text timesGotHitText;
	timesGotHitText.setFont(font);
	timesGotHitText.setCharacterSize(20);
	timesGotHitText.setFillColor(sf::Color::White);


	// Calculate remaining time and display
	sf::Time remainingTime = gameTimeLimit - gameClock.getElapsedTime();
	timerText.setString("Time: " + std::to_string(static_cast<int>(remainingTime.asSeconds())) + " s");
	timerText.setPosition(view.getCenter().x + view.getSize().x / 2 - 150, view.getCenter().y - view.getSize().y / 2 + 10);

	scoreText.setString("Score: " + std::to_string(getScore()));
	scoreText.setPosition(view.getCenter().x + view.getSize().x / 2 - 150, view.getCenter().y - view.getSize().y / 2 + 50);

	timesGotHitText.setString("Times got hit: " + std::to_string(getTimesGotHit()));
	timesGotHitText.setPosition(view.getCenter().x + view.getSize().x / 2 - 150, view.getCenter().y - view.getSize().y / 2 + 90);


	window.draw(timerText);
	window.draw(scoreText);
	window.draw(timesGotHitText);

	window.display();
}

void Window::drawWorld() {
	window.draw(myIcons.allSprites[3]);
	//we can set position of our pngs and draw one by one...
	for (int i = 0; i < myWorld.getVerticalBlockNumber(); i++) {
		for (int j = 0; j < myWorld.getHorizontalBlockNumber(); j++) {
			if (myWorld.getWorld()[i][j] == 3) { continue; }
			myIcons.allSprites[myWorld.getWorld()[i][j]].setPosition(j * myWorld.getTileSize(), i * myWorld.getTileSize());
			window.draw(myIcons.allSprites[myWorld.getWorld()[i][j]]);
		}
	}


}

void Window::drawCharacter() {
	int character_png_index = 0;
	bool flagIsFalling = false;
	bool flagIsJumping = false;
	bool flagGoingRight = false;
	bool flagGoingLeft = false;
	
	//Falling,

	checkSpike = false;
	checkLava = false;
	checkLadder = false;

	leftCollisions();
	rightCollisions();
	upCollisions();
	bottomCollisions();
	if (checkLava) {
		if (lavatimer > 0 && lavatimer < 120) {
			// Player touched lava within the last 4 seconds, return or handle accordingly
		}
		else {
			lavatimer = 0;
			resetGameState();
		}

		lavatimer++;
	}
	else {
		lavatimer = 0;
	}
	
	if (checkSpike) {
		drawGameOverScreen();
		return;
	}

	bottomCollisions();
	if (checkLadder) {
		if (kListener.isSPressed() && myCharacter.canGoDown) {
			for (int i = 0; i < 5; i++) {
				bottomCollisions();
				if (checkLadder) {
					myCharacter.coordinate.y += 1;
				}
			}
		}		
	}
	else if (myCharacter.canGoDown && !myCharacter.jumping) {
		std::cout << myCharacter.staticFall << std::endl;
		int loop = static_cast<int>(myCharacter.speed.y * 1 / 60 * (myCharacter.staticFall += 2));

		
		
			for (int i = 0; i < loop; i++) {
				bottomCollisions();

				if (myCharacter.canGoDown) {
					myCharacter.coordinate.y += 1;
					flagIsFalling = true;
					if (flagGoingLeft) {
						character_png_index = 6;
					}
					else {
						character_png_index = 5;
					}
				}
			}
		
	}
	else {
		myCharacter.staticFall = 1;
		flagIsFalling = false;
	}

	checkLadder = false;
	upCollisions();
	if (checkLadder) {
		if (kListener.isWPressed()&& myCharacter.canGoUp) {
			for (int i = 0; i < 5; i++) {
				upCollisions();
				if (checkLadder) {
					myCharacter.coordinate.y -= 1;
				}
			}
		}
		
	}
	else if (kListener.isWPressed() && myCharacter.canGoUp) {
		int loop = static_cast<int>(myCharacter.speed.y * 1 / 60 * (myCharacter.staticJump -= 2));
		if (loop <= 0) {
			myCharacter.staticJump = 115;
			kListener.wPressed = false;

		}
		
			for (int i = 0; i < loop; i++) {
				upCollisions();
				if (myCharacter.canGoUp && kListener.isWPressed()) {
					myCharacter.coordinate.y -= 1;
					flagIsJumping = true;
				}
				else {
					kListener.wPressed = false;
					flagIsJumping = false;
					myCharacter.staticJump = 115;
				}
			}
		
	}
	else {
		myCharacter.staticJump = 115;
		kListener.wPressed = false;
	}

	//going left;
	for (int i = 0; i < myCharacter.speed.x; i++) {
		leftCollisions();
		if (kListener.isAPressed() && myCharacter.canGoLeft) {

			myCharacter.coordinate.x -= 1;
			flagGoingLeft = true;
			if (flagIsFalling || flagIsJumping) {
				character_png_index = 6;
			}
			else {
				character_png_index = 4;
			}
		}
		else {
			flagGoingLeft = false;
		}
	}
	//going right
	for (int i = 0; i < myCharacter.speed.x; i++) {
		rightCollisions();
		if (kListener.isDPressed() && myCharacter.canGoRight) {
			myCharacter.coordinate.x += 1;
			flagGoingLeft = true;
			if (flagIsFalling || flagIsJumping) {
				character_png_index = 5;
			}
			else {
				character_png_index = 0;
			}
		}
		else {
			flagGoingLeft = false;
		}
	}

	myCharacter.canGoDown = true;
	myCharacter.canGoLeft = true;
	myCharacter.canGoRight = true;
	myCharacter.canGoUp = true;

	myIcons.allSprites[character_png_index].setPosition(myCharacter.coordinate);
	window.draw(myIcons.allSprites[character_png_index]);
}


void Window::leftCollisions() {

	sf::FloatRect characterLeft(myCharacter.coordinate.x, myCharacter.coordinate.y
		, 1, myCharacter.getSize());

	int jCharacter = myCharacter.coordinate.x / myCharacter.getSize();
	int iCharacter = myCharacter.coordinate.y / myCharacter.getSize();

	for (int i = iCharacter - 1; i < iCharacter + 2; i++) { //3 x 2 search only if i in the middle of tiles.
		for (int j = jCharacter; j < jCharacter + 2; j++) {
			if (i >= 0 && i < 10 && j >= 0 && j < myWorld.getHorizontalBlockNumber()) {
				if (myWorld.getWorld()[i][j] == 14) {
					sf::FloatRect ladder(j * myWorld.getTileSize() , i * myWorld.getTileSize()
						, 64, 64);
					if (characterLeft.intersects(ladder)) {
						checkLadder = true;
						continue;
					}
					
				}
				if (myWorld.getWorld()[i][j] == 1 || myWorld.getWorld()[i][j] == 2 || myWorld.getWorld()[i][j] == 12) {
					sf::FloatRect tileRight(j * myWorld.getTileSize() + 63, i * myWorld.getTileSize()
						, 1, myWorld.getTileSize());
					if (characterLeft.intersects(tileRight)) {
						myCharacter.canGoLeft = false;
					}
				}
				//Collision for spikes
				if (myWorld.getWorld()[i][j] == 7) {
					sf::FloatRect spikeHitbox(j * myWorld.getTileSize(), i * myWorld.getTileSize() + 38
						, 64, myWorld.getTileSize() - 38);
					if (characterLeft.intersects(spikeHitbox)) {
						checkSpike = true;
						
					}
				}//Collision for lava
				if (myWorld.getWorld()[i][j] == 9) {
					sf::FloatRect tileLava(j * myWorld.getTileSize() + 63, i * myWorld.getTileSize(), 1, myWorld.getTileSize());

					if (characterLeft.intersects(tileLava)) {
						checkLava = true;
						myCharacter.canGoLeft = false;

					}
					
				}
				else if (myCharacter.coordinate.x == 0) {
					myCharacter.canGoLeft = false;
				}
			}
		}
	}
}
void Window::rightCollisions() {

	sf::FloatRect characterRight(myCharacter.coordinate.x + 64, myCharacter.coordinate.y
		, 1, myCharacter.getSize());

	int jCharacter = myCharacter.coordinate.x / myCharacter.getSize();
	int iCharacter = myCharacter.coordinate.y / myCharacter.getSize();

	for (int i = iCharacter - 1; i < iCharacter + 2; i++) { //3 x 2 search only if i in the middle of tiles.
		for (int j = jCharacter; j < jCharacter + 2; j++) {
			if (i >= 0 && i < 10 && j >= 0 && j < myWorld.getHorizontalBlockNumber()) {
				if (myWorld.getWorld()[i][j] == 14) {
					sf::FloatRect ladder(j * myWorld.getTileSize(), i * myWorld.getTileSize()
						, 64, 64);
					if (characterRight.intersects(ladder)) {
						checkLadder = true;
						continue;
					}
				}
				if (myWorld.getWorld()[i][j] == 1 || myWorld.getWorld()[i][j] == 2 || myWorld.getWorld()[i][j] == 12) {
					sf::FloatRect tileLeft(j * myWorld.getTileSize(), i * myWorld.getTileSize()
						, 1, myWorld.getTileSize());
					if (characterRight.intersects(tileLeft)) {
						myCharacter.canGoRight = false;
					}
				}//Collision for lava
				if (myWorld.getWorld()[i][j] == 9) {
					sf::FloatRect tileLava(j * myWorld.getTileSize(), i * myWorld.getTileSize()
						, 1, myWorld.getTileSize());

					if (characterRight.intersects(tileLava)) {
						checkLava = true;
						myCharacter.canGoRight = false;

					}
					
				}
				
				else if (myCharacter.coordinate.x + 64 == myWorld.getHorizontalBlockNumber() * myWorld.getTileSize()) {
					myCharacter.canGoRight = false;
				}
			}
		}
	}
}
void Window::upCollisions() {

	sf::FloatRect characterUp(myCharacter.coordinate.x, myCharacter.coordinate.y
		, myCharacter.getSize(), 1);

	int jCharacter = myCharacter.coordinate.x / myCharacter.getSize();
	int iCharacter = myCharacter.coordinate.y / myCharacter.getSize();

	for (int i = iCharacter - 1; i < iCharacter + 2; i++) { //3 x 2 search only if i in the middle of tiles.
		for (int j = jCharacter; j < jCharacter + 2; j++) {
			if (i >= 0 && i < 10 && j >= 0 && j < myWorld.getHorizontalBlockNumber()) {
				if (myWorld.getWorld()[i][j] == 14) {
					sf::FloatRect ladder(j * myWorld.getTileSize(), i * myWorld.getTileSize()
						, 64, 64);
					if (characterUp.intersects(ladder)) {
						checkLadder = true;
						continue;
					}
					
				}
				if (myWorld.getWorld()[i][j] == 1 || myWorld.getWorld()[i][j] == 2 || myWorld.getWorld()[i][j] == 12) {
					sf::FloatRect tileDown(j * myWorld.getTileSize(), i * myWorld.getTileSize() + 64
						, myWorld.getTileSize() - 1, 1);
					if (characterUp.intersects(tileDown)) {
						myCharacter.canGoUp = false;
					}
				}//Collision for lava
				if (myWorld.getWorld()[i][j] == 9) {
					sf::FloatRect tileLava(j * myWorld.getTileSize(), i * myWorld.getTileSize() + 64
						, myWorld.getTileSize() - 1, 1);

					if (characterUp.intersects(tileLava)) {
						checkLava = true;
						myCharacter.canGoUp = false;

					}

				}
				
				else if (myCharacter.coordinate.y == 0) {
					myCharacter.canGoUp = false;
				}
			}
		}
	}
}
void Window::bottomCollisions() {

	sf::FloatRect characterDown(myCharacter.coordinate.x, myCharacter.coordinate.y + 64
		, myCharacter.getSize(), 1);

	int jCharacter = myCharacter.coordinate.x / myCharacter.getSize();
	int iCharacter = myCharacter.coordinate.y / myCharacter.getSize();

	for (int i = iCharacter - 1; i < iCharacter + 2; i++) { //3 x 2 search only if i in the middle of tiles.
		for (int j = jCharacter; j < jCharacter + 2; j++) {
			if (i >= 0 && i < 10 && j >= 0 && j < myWorld.getHorizontalBlockNumber()) {
				if (myWorld.getWorld()[i][j] == 14) {
					
					sf::FloatRect ladder(j * myWorld.getTileSize(), i * myWorld.getTileSize()
						, 64, 64);

					if(characterDown.intersects(ladder)){
						checkLadder = true;
						continue;
					}
					
				}
				if (myWorld.getWorld()[i][j] == 1 || myWorld.getWorld()[i][j] == 2 || myWorld.getWorld()[i][j] == 12 || myWorld.getWorld()[i][j] == 13) {
					sf::FloatRect tileUp(j * myWorld.getTileSize(), i * myWorld.getTileSize()
						, myWorld.getTileSize() - 1, 1);
					if (characterDown.intersects(tileUp)) {
						myCharacter.canGoDown = false;
					}
				}//Collision for lava
				if (myWorld.getWorld()[i][j] == 9) {
					sf::FloatRect tileLava(j * myWorld.getTileSize(), i * myWorld.getTileSize()
						, myWorld.getTileSize() - 1, 1);

					if (characterDown.intersects(tileLava)) {
						checkLava = true;
						myCharacter.canGoDown = false;

					}

				}
				
				else if (myCharacter.coordinate.y + 64 == window.getSize().y) {
					myCharacter.canGoDown = false;
					this->sounds.soundLibrary[2].play();
					drawGameOverScreen();
				}
			}
		}
	}
}

void Window::checkEndState() {
	if (timesGotHit >= 4 || score <= 0) {
		inGameOverScreen = true;
		inGame = false;
		inDisplayScoresMenu = false;
		inLevelOverScreen = false;
		inMainMenu = false;
	}
	if (inGame && myCharacter.coordinate.x >= 2300) {
		inGameOverScreen = false;
		inGame = false;
		inDisplayScoresMenu = false;
		inLevelOverScreen = true;
		inMainMenu = false;
	}
}








