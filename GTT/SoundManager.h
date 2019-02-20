#pragma once
#include "Container.h"
#include <SDL_mixer.h>
#include <map>

class SoundManager {
public:
	SoundManager();
	virtual ~SoundManager();

	bool loadSound(string path, string name);
	// Returns the channel in which the sound will be played
	int playSound(string name, int loops);
	void pauseSound(int channel);
	void resumeSound(int channel);
	bool isSoundPlaying(int channel);
	bool soundExists(string name);

	bool loadMusic(string path, string name);
	void playMusic(string name, int loops);
	void pauseMusic();
	void resumeMusic();
	bool isMusicPlaying();
	bool musicExists(string name);

private:
	map<string, Mix_Music*> music_;
	map<string, Mix_Chunk*> sound_;
};

