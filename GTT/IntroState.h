#pragma once
#include "MpegState.h"
class IntroState :
	public MpegState
{
public:

	IntroState(SDL_Window* win, SDL_Renderer* rend);

	virtual ~IntroState();
};

