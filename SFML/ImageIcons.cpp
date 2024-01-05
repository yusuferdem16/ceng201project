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
	allTextures[7].loadFromFile("spike_trap.png");
	allTextures[8].loadFromFile("level_end_flag.png");
	allTextures[9].loadFromFile("lava.png");
	allTextures[10].loadFromFile("chest.png");
	allTextures[11].loadFromFile("craftingtable.jpg");
	allTextures[12].loadFromFile("tas.png");
	allTextures[13].loadFromFile("platform.png");
	allTextures[14].loadFromFile("ladder.png");
	//...gonna add more here... 
	//---------------------------------

	//assing every texture to it's Sprites we can do this with a loop (benefits of vectors)
	for (int i = 0; i < imageNumber; i++) {
		if (i == 10) {
			allSprites[i].setScale(0.5, 0.5);
		}
		allSprites[i].setTexture(allTextures[i]);
	}

}
/*
void ImageIcons::implementImages() {

	allTextures = std::vector<sf::Texture>(imageNumber);
	allSprites = std::vector<sf::Sprite>(imageNumber);

	//implementing images individually
	allTextures[0].loadFromFile("character_64.png");
	allTextures[1].loadFromFile("grass_64.png");
	allTextures[2].loadFromFile("dirt_64.png");
	allTextures[3].loadFromFile("background.jpg");
	//Character walking left
	allTextures[4].loadFromFile("first_frame_left.png");
	allTextures[5].loadFromFile("character_64_walking_left.png");
	allTextures[6].loadFromFile("character_64_looking_left.png");
	//Character walking right
	allTextures[7].loadFromFile("first_frame_right.png");
	allTextures[8].loadFromFile("character_64_walking_right.png");
	allTextures[9].loadFromFile("character_64_looking_right.png");
	//Character jumping
	allTextures[10].loadFromFile("character_64_jumping.png");
	allTextures[11].loadFromFile("character_64_jumping_left.png");
	//...gonna add more here...
	//---------------------------------

	//assing every texture to it's Sprites we can do this with a loop (benefits of vectors)
	for (int i = 0; i < imageNumber; i++) {
		allSprites[i].setTexture(allTextures[i]);
	}

}*/