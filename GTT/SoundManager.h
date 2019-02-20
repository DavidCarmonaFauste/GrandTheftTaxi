#pragma once
#include "Container.h"
#include <SDL_mixer.h>
#include <map>

class SoundManager {
public:
	SoundManager();
	virtual ~SoundManager();

	bool loadSound(string path, string name);
	void playSound(string name);
	void pauseSound();
	void resumeSound();
	bool isSoundPlaying();
	bool soundExists(string name);

	bool loadMusic();
	void playMusic();
	void pauseMusic();
	void resumeMusic();
	bool isMusicPlaying();
	bool musicExists(string name);

private:
	map<string, Mix_Music*> music_;
	map<string, Mix_Chunk*> sound_;
};

