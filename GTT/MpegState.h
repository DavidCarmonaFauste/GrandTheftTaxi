#pragma once
#include "GameState.h"
#include "VideoManager.h"



class MpegState :
	public GameState
{
public:

	//builds
	MpegState(SDL_Window* win, SDL_Renderer* rend);
	virtual ~MpegState();

	virtual void start() override;
	virtual void end() override;

	//redefine methods - not necessary  for video decoder player
	virtual void update(Uint32 deltaTime) {}
	virtual void handleEvents(Uint32 deltaTime, SDL_Event& event) {}
	virtual void render(Uint32 deltaTime) const {}

	void setVideoId(videoId videoId);
	virtual void playSequence();

private:
	VideoManager* videoManager_ = nullptr;
	videoId videoId_;
};

