#ifndef MOUSELISTENER_H
#define MOUSELISTENER_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Window;  // Forward declaration

class mouseListener {
private:
    int x;
    int y;
    Window* w;  // Change this to a pointer
    Window* defaultWindow;  // Change this to a pointer

public:
    mouseListener();
    void Listen(const sf::Event& event);
    int getX();
    int getY();
    void setX(int x);
    void setY(int y);
};

#endif
