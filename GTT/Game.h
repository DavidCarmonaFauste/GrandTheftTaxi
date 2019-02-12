#pragma once

#include "SDL.h"

using namespace std;

// Forward declarations
class Animation;

class Game {
public:
	Game(SDL_Window *window_, SDL_Renderer *renderer_);
	virtual ~Game();

	bool update(Uint32 deltaTime);
	void handleEvents(Uint32 deltaTime);
	void render(Uint32 deltaTime);

	static SDL_Renderer *renderer_;
	static SDL_Window *window_;

private:
	bool exit_ = false;

	// FOR TESTING
	Animation *test;
};

