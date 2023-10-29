#include "Window.h"

Window::Window() : window(sf::VideoMode(800, 800), ""), mListener(*this) {

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
			keyListener(event);
			drawGraphics();
		}
	}
}

void Window::keyListener(const sf::Event& event) {

	//keyPressed
	if (event.type == sf::Event::KeyPressed) {
		//Example W pressed
		if (event.key.code == sf::Keyboard::W) {
			std::cout << "pressed w";
		}
	}
	if (event.type == sf::Event::KeyReleased) {

	}
}

void Window::implementation() {

	shape.setFillColor(sf::Color(204, 77, 5));
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


