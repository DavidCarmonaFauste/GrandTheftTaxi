#pragma once

#include "SDL.h"
#include "GameManager.h"

using namespace std;

// Forward declarations
class Sprite;

class Game {
public:
	Game(SDL_Window *window_, SDL_Renderer *renderer_);
	virtual ~Game();

	bool update(double deltaTime);
	void handleEvents();

	static SDL_Renderer *renderer;
	static SDL_Window *window;

private:
	//Managers
	GameManager* GM;

	// TESTING
	Sprite *test;

	bool exit = false;
};

