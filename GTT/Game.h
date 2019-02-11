#pragma once

#include "SDL.h"

using namespace std;

// Forward declarations
class Sprite;

class Game {
public:
	Game(SDL_Window *window_, SDL_Renderer *renderer_);
	virtual ~Game();

	bool update(double deltaTime);
	void handleEvents();

	static SDL_Renderer *renderer_;
	static SDL_Window *window_;

private:
	bool exit_ = false;

	// FOR TESTING
	Sprite *test;
};

