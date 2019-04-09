#include "MpegState.h"
#include "Game.h"


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
	/*if (VIDEO_NEXTSTATE.find(videoId_) != VIDEO_NEXTSTATE.end())
		Game::getInstance()->setState(VIDEO_NEXTSTATE.at(videoId_));*/

}


void MpegState::setVideoId(videoId videoId) {
	videoId_ = videoId;
}

void MpegState::playSequence() {
	videoManager_->PlayVideoSequence(VIDEOS.at(videoId_));
	Game::getInstance()->getGameStateMachine()->setState(NAME_MAINMENU_STATE);
}
