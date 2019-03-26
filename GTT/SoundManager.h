#pragma once
#include "Container.h"
#include <SDL_mixer.h>

class SoundManager {
public:
	SoundManager();
	virtual ~SoundManager();

	// DON'T USE THIS DIRECTLY,
	// USE THE RESOURCES SHEET INSTEAD !!!
	bool loadSound(string path, soundId id);

	// Returns the channel in which the sound will be played
	int playSound(soundId id, int loops);
	void pauseSound(int channel);
	void resumeSound(int channel);
	bool isSoundPlaying(int channel);
	bool soundExists(soundId id);
	
	// DON'T USE THIS DIRECTLY,
	// USE THE RESOURCES SHEET INSTEAD !!!
	bool loadMusic(string path, musicId id);

	void playMusic(musicId id, int loops);
	void pauseMusic();
	void resumeMusic();
	bool isMusicPlaying();
	bool musicExists(musicId id);

private:
	map<musicId, Mix_Music*> loadedMusic_;
	map<soundId, Mix_Chunk*> loadedSounds_;
};

