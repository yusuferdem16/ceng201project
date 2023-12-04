#include "Window.h"

Window::Window(Level level) : level(level), myWorld(level.world),
mListener(*this), kListener(*this), myIcons(*this), myCharacter(*this)
, window(sf::VideoMode(20 * 64
	, 10 * 64), ""),
	view(sf::Vector2f(0.0f, 0.0f),
		sf::Vector2f(20 * 64
			, 10 * 64)) {
}

void Window::run() {

	implementation();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) {
				window.close();
			}

			mListener.Listen(event);
			kListener.Listen(event);

		}
		drawGraphics();
	}
}

void Window::implementation() {
	window.setFramerateLimit(60);
}

void Window::drawGraphics() {

	window.clear(sf::Color(255, 255, 255));

	/*window.draw(myIcons.allSprites[0]);
	 0 th element is character_64.png at this point.
	we can use a for loop for every sprite when we need*/

	window.clear();

	//karakter solda
	if (myCharacter.coordinate.x < 10 * 64 - 32) {
		view.setCenter(sf::Vector2f(20 * 64 / 2, 10 * 64 / 2));
	}
	//karakter saðda
	else if (myCharacter.coordinate.x > myWorld.getHorizontalBlockNumber() * myWorld.getTileSize() - 10 * 64 - 32) {
		view.setCenter(sf::Vector2f(myWorld.getHorizontalBlockNumber() * myWorld.getTileSize() - 10 * 64, 10 * 64 / 2));
	}
	//ekran kayýyor
	else {
		view.setCenter(sf::Vector2f(myCharacter.coordinate.x + 32, 10 * 64 / 2));
	}

	window.setView(view);
	drawWorld();
	drawCharacter();
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
	//Falling
	bottomCollisions();
	if (myCharacter.canGoDown && !myCharacter.jumping) {
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

	upCollisions();
	if (kListener.isWPressed() && myCharacter.canGoUp) {
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
				if (myWorld.getWorld()[i][j] == 1 || myWorld.getWorld()[i][j] == 2) {
					sf::FloatRect tileRight(j * myWorld.getTileSize() + 63, i * myWorld.getTileSize()
						, 1, myWorld.getTileSize());
					if (characterLeft.intersects(tileRight)) {
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
				if (myWorld.getWorld()[i][j] == 1 || myWorld.getWorld()[i][j] == 2) {
					sf::FloatRect tileLeft(j * myWorld.getTileSize(), i * myWorld.getTileSize()
						, myWorld.getTileSize(), myWorld.getTileSize());
					if (characterRight.intersects(tileLeft)) {
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
				if (myWorld.getWorld()[i][j] == 1 || myWorld.getWorld()[i][j] == 2) {
					sf::FloatRect tileDown(j * myWorld.getTileSize(), i * myWorld.getTileSize() + 64
						, myWorld.getTileSize() - 1, 1);
					if (characterUp.intersects(tileDown)) {
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
				if (myWorld.getWorld()[i][j] == 1 || myWorld.getWorld()[i][j] == 2) {
					sf::FloatRect tileUp(j * myWorld.getTileSize(), i * myWorld.getTileSize()
						, myWorld.getTileSize() - 1, 1);
					if (characterDown.intersects(tileUp)) {
						myCharacter.canGoDown = false;
					}
				}
				else if (myCharacter.coordinate.y + 64 == window.getSize().y) {
					myCharacter.canGoDown = false;
				}
			}
		}
	}
}






