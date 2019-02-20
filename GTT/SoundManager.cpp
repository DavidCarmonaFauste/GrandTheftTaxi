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

int SoundManager::playSound(string name, int loops) {
	return Mix_PlayChannel(-1, sound_[name], loops);
}

void SoundManager::pauseSound(int channel) {
	Mix_Pause(channel);
}

void SoundManager::resumeSound(int channel) {
	Mix_Resume(channel);
}

bool SoundManager::isSoundPlaying(int channel) {
	return Mix_Playing(channel);
}

bool SoundManager::soundExists(string name) {
	return sound_.find(name) != sound_.end();
}

bool SoundManager::loadMusic(string path, string name) {
	music_[name] = Mix_LoadMUS(path.c_str());

	if (music_[name] != nullptr) return true;
	else return false;
}

void SoundManager::playMusic(string name, int loops) {
	Mix_PlayMusic(music_[name], loops);
}

void SoundManager::pauseMusic() {
	Mix_PauseMusic();
}

void SoundManager::resumeMusic() {
	Mix_ResumeMusic();
}

bool SoundManager::isMusicPlaying() {
	return Mix_PlayingMusic();
}

bool SoundManager::musicExists(string name) {
	return music_.find(name) != music_.end();
}
