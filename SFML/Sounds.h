#pragma once
#include <SFML/Audio.hpp>

class Window;

//We will use the OGG and FLAC formats for the sound effects 
class Sounds {
private:
	Window& w;
	sf::Sound sound;
	sf::SoundBuffer soundBuffer;
	int numberOfSounds; //Placeholder number
public:
	Sounds(Window& w);
	std::vector<sf::Sound> soundLibrary;
	std::vector<sf::SoundBuffer> soundBufferCollection;
	void setSounds();
};
