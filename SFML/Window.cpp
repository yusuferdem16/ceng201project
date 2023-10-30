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

}

void Window::drawGraphics() {

	window.clear(sf::Color(18, 33, 43));
	window.draw(shape);
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

