#include "SoundManager.h"



SoundManager::SoundManager() {
	deviceSpecs_.freq = 44100;
	deviceSpecs_.format = AUDIO_S16;
	deviceSpecs_.channels = 2;
	deviceSpecs_.samples = 1024;

	SDL_OpenAudio(&deviceSpecs_, NULL);
}


SoundManager::~SoundManager() {

}
