#include "MpegState.h"



MpegState::MpegState(SDL_Window* win, SDL_Renderer* rend)
{
	videoManager_ = new VideoManager(win, rend);	
}


MpegState::~MpegState()
{
	delete videoManager_; videoManager_ = nullptr;
}

void MpegState::start() {
	playSequence();
}


void MpegState::setVideoId(videoId videoId) {
	videoId_ = videoId;
}

void MpegState::playSequence() {
	videoManager_->PlayVideoSequence(VIDEOS.at(videoId_));
}
