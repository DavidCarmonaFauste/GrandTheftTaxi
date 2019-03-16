#include "SoundManager.h"



SoundManager::SoundManager() {
	// Load the music files from the resources sheet
	for (int i = 0; i < Resources::getInstance()->music_.size(); i++) {
		loadMusic(Resources::getInstance()->music_[i].path,
					Resources::getInstance()->music_[i].id);
	}
	
	// Load the sound files from the resources sheet
	for (int i = 0; i < Resources::getInstance()->sounds_.size(); i++) {
		loadSound(Resources::getInstance()->sounds_[i].path,
			Resources::getInstance()->sounds_[i].id);
	}
}


SoundManager::~SoundManager() {
	for (map<Resources::MusicId, Mix_Music*>::iterator it = music_.begin(); it != music_.end(); it++) {
		Mix_FreeMusic(it->second);
		it->second = nullptr;
	}
	music_.clear();

	for (map<Resources::SoundId, Mix_Chunk*>::iterator it = sound_.begin(); it != sound_.end(); it++) {
		Mix_FreeChunk(it->second);
		it->second = nullptr;
	}
	sound_.clear();
}


// NO NEED TO USE THIS DIRECTLY,
// USE THE RESOURCES SHEET INSTEAD !!!
bool SoundManager::loadSound(string path, Resources::SoundId id) {
	sound_[id] = Mix_LoadWAV(path.c_str());

	if (sound_[id] != nullptr) return true;
	else return false;
}

int SoundManager::playSound(Resources::SoundId id, int loops) {
	return Mix_PlayChannel(-1, sound_[id], loops);
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

bool SoundManager::soundExists(Resources::SoundId id) {
	return sound_.find(id) != sound_.end();
}

bool SoundManager::loadMusic(string path, Resources::MusicId id) {
	music_[id] = Mix_LoadMUS(path.c_str());

	if (music_[id] != nullptr) return true;
	else return false;
}

void SoundManager::playMusic(Resources::MusicId id, int loops) {
	Mix_PlayMusic(music_[id], loops);
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

bool SoundManager::musicExists(Resources::MusicId id) {
	return music_.find(id) != music_.end();
}
