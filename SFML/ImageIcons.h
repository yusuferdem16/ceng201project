#pragma once

#include <SFML/Graphics.hpp>

class Window;

class ImageIcons {
private:
	Window& w;
	int imageNumber = 10;
public:
	std::vector<sf::Texture> allTextures; // for now we assume we have only 10 textures!
	std::vector<sf::Sprite> allSprites; // 10 sprites for 10 textures.		
	ImageIcons(Window& w);
	void implementImages();
};