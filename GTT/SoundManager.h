#pragma once
#include "Container.h"

class SoundManager {
public:
	SoundManager();
	virtual ~SoundManager();

private:
	SDL_AudioSpec deviceSpecs_;
};

