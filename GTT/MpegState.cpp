#include "MpegState.h"



MpegState::MpegState(SDL_Window* win, SDL_Renderer* rend)
{
	videoManager_ = new VideoManager(win, rend);	
}


MpegState::~MpegState()
{
	delete videoManager_; videoManager_ = nullptr;
}


void MpegState::playSequence(string s) {

	videoManager_->PlayVideoSequence(s);
}
