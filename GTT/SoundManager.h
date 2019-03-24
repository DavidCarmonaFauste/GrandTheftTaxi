#pragma once
#include "Container.h"
#include "Resources.h"
#include <SDL_mixer.h>
#include <map>

class SoundManager {
public:
	SoundManager();
	virtual ~SoundManager();

	// DON'T USE THIS DIRECTLY,
	// USE THE RESOURCES SHEET INSTEAD !!!
	bool loadSound(string path, Resources::SoundId id);

	// Returns the channel in which the sound will be played
	int playSound(Resources::SoundId id, int loops);
	void pauseSound(int channel);
	void resumeSound(int channel);
	bool isSoundPlaying(int channel);
	bool soundExists(Resources::SoundId id);

	
	// DON'T USE THIS DIRECTLY,
	// USE THE RESOURCES SHEET INSTEAD !!!
	bool loadMusic(string path, Resources::MusicId id);

	void playMusic(Resources::MusicId id, int loops);
	void pauseMusic();
	void resumeMusic();
	bool isMusicPlaying();
	bool musicExists(Resources::MusicId id);

private:
	map<Resources::MusicId, Mix_Music*> music_;
	map<Resources::SoundId, Mix_Chunk*> sound_;
};

