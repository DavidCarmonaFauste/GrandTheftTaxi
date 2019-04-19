#pragma once
#include "Container.h"
#include <SDL_mixer.h>
#include "Observable.h"

class SoundManager: public Observable {
public:
	static SoundManager *getInstance();

	//Methods to define how many channels we can use
	int setAlloctaedChannels(int n);

	// DON'T USE THIS DIRECTLY,
	// USE THE RESOURCES SHEET INSTEAD !!!
	bool loadSound(string path, soundId id);

	// Returns the channel in which the sound will be played
	int playSound_Ch(int channel, soundId id, int loops); //secundary
	int playSound(soundId id, int loops);//primary


	//pause and resume de specific channel
	void pauseSound(int channel);
	void resumeSound(int channel);

	//stop and Channel
	int stopSound(int channel);

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

	//Mix_Volume sets the volume of a channel specified. The amount passed to volume can be between 0 and MIX_MAX_VOLUME which equals 128.
	void setVolumeSound(int& channel, const int& v);
	//channel -1: set volume in all channels
	//especified -1 in volume parameter for return current volume value of channel
	int getVolumeSound(int& channel, const int& v = -1);

	int getMIX_MAX_VOLUME();


private:
	static SoundManager *singleton_;

	SoundManager();
	virtual ~SoundManager();

	map<musicId, Mix_Music*> loadedMusic_;
	map<soundId, Mix_Chunk*> loadedSounds_;

	static void channelDone(int channel);

};

