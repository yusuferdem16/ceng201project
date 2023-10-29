#include "mouseListener.h"


mouseListener::mouseListener() : w(defaultWindow), x(0), y(0) {

}

mouseListener::mouseListener(Window& w) : w(w) ,x(0) , y(0){
	
}

void mouseListener::Listen(const sf::Event& event) {

	//mousePressed
	if (event.type == sf::Event::MouseButtonPressed) {		
		x = event.mouseButton.x;
		y = event.mouseButton.y;
	}
	//mouseReleased
	if (event.type == sf::Event::MouseButtonReleased) {

	}
	//mouse Hover Effect
	if (event.type == sf::Event::MouseMoved) {
		x = event.mouseMove.x;
		y = event.mouseMove.y;
		std::cout << "x:" << x << " y:" << y;
	}
}

int mouseListener::getX() {
	return x;
}

int mouseListener::getY() {
	return y;
}

void mouseListener::setX(int newX) {
	x = newX;
}

void mouseListener::setY(int newY) {
	y = newY;
}