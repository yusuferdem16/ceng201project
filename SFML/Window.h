#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <SFML/Graphics.hpp>

class mouseListener;  // Forward declaration

class Window {
private:
    int x;
    int y;
    sf::RenderWindow window;
    sf::CircleShape shape;
    mouseListener* mListener;  // Change this to a pointer
public:
    Window();
    void run();
    void implementation();
    void drawGraphics();
    void keyListener(const sf::Event& e);
    void start();
    void setMouseListener(mouseListener* listener);  // Add a method to set the mouseListener
};

#endif
