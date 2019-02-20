#include "SoundManager.h"



SoundManager::SoundManager() {

}


SoundManager::~SoundManager() {
	for (map<string, Mix_Music*>::iterator it = music_.begin(); it != music_.end(); it++) {
		Mix_FreeMusic(it->second);
		it->second = nullptr;
	}
	music_.clear();

	for (map<string, Mix_Chunk*>::iterator it = sound_.begin(); it != sound_.end(); it++) {
		Mix_FreeChunk(it->second);
		it->second = nullptr;
	}
	sound_.clear();
}

bool SoundManager::loadSound(string path, string name) {
	sound_[name] = Mix_LoadWAV(path.c_str());

	if (sound_[name] != nullptr) return true;
	else return false;
}

void SoundManager::playSound(string name) {
	Mix_PlayChannel(-1, sound_[name], 0);
}

