#include "Window.h"

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
			std::cout << getX() << " " << getY() << "\n";
			drawGraphics();
		}
	}
}

void Window::implementation() {

	shape.setFillColor(sf::Color(255, 0, 0));
	shape.setPosition(200, 200);

	//we can set position of our pngs here... as we did to shape

}

void Window::drawGraphics() {

	window.clear(sf::Color(255, 255, 255));
	//window.draw(shape); no need to draw shape for now.			
	window.draw(myIcons.allSprites[0]); /* 0 th element is WARJET.png at this point.
										we can use a for loop for every sprite when we need*/
	window.display();
}

void Window::start() {
	run();
}

int Window::getX() {
	return mListener.getX();
}

int Window::getY() {
	return mListener.getY();
}

