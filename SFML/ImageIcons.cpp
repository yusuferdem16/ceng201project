#include "ImageIcons.h"

ImageIcons::ImageIcons(Window& w) : w(w) {
	implementImages();
}

void ImageIcons::implementImages() {

	allTextures = std::vector<sf::Texture>(imageNumber);
	allSprites = std::vector<sf::Sprite>(imageNumber);

	//implementing images individually
	allTextures[0].loadFromFile("WARJET.png");
	//...gonna add more here...
	//---------------------------------

	//assing every texture to it's Sprites we can do this with a loop (benefits of vectors)
	for (int i = 0; i < imageNumber; i++) {
		allSprites[i].setTexture(allTextures[i]);
	}

}