#include "Sounds.h"

Sounds::Sounds(Window& w) : w(w) , numberOfSounds(5) {
	setSounds();
}
void Sounds::setSounds() {
	soundLibrary = std::vector<sf::Sound>(numberOfSounds);
	soundBufferCollection = std::vector<sf::SoundBuffer>(numberOfSounds);
	//Load sound into buffer
	soundBufferCollection[0].loadFromFile("theme.ogg");
	//Set the buffer up with a sound
	soundLibrary[0].setBuffer(soundBufferCollection[0]);
	/* Because soundBuffer only accepts a string(as an address), an inputStream
	or a sound file from memory and we will only use a few sound effects,
	I see no need for a loop and we can just insert them on our own, although
	one could be made if the need arises */
	//soundLibrary[0].play();
}