#include "ImageIcons.h"

ImageIcons::ImageIcons(Window& w) : w(w) {
	implementImages();
}

void ImageIcons::implementImages() {

	allTextures = std::vector<sf::Texture>(imageNumber);
	allSprites = std::vector<sf::Sprite>(imageNumber);

	//implementing images individually
	allTextures[0].loadFromFile("character_64.png");
	allTextures[1].loadFromFile("grass_64.png");
	allTextures[2].loadFromFile("dirt_64.png");
	allTextures[3].loadFromFile("background.jpg");
	allTextures[4].loadFromFile("character_64_looking_left.png");
	allTextures[5].loadFromFile("character_64_jumping.png");
	allTextures[6].loadFromFile("character_64_jumping_left.png");
	//...gonna add more here... (I sure hope so)
	//---------------------------------

	//assing every texture to it's Sprites we can do this with a loop (benefits of vectors)
	for (int i = 0; i < imageNumber; i++) {
		allSprites[i].setTexture(allTextures[i]);
	}

}