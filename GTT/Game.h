#pragma once

#include "SDL.h"
#include "GameStateMachine.h"


using namespace std;
typedef unsigned int uint;

// Forward declarations
class Animation;

class Game {
public:
	Game(SDL_Window *window_, SDL_Renderer *renderer_);
	virtual ~Game();

	/*bool update(Uint32 deltaTime);
	void handleEvents(Uint32 deltaTime);
	void render(Uint32 deltaTime);*/

	void run(uint deltaTime);
	bool exitGame();

	static SDL_Renderer *renderer_;
	static SDL_Window *window_;

private:
	bool exit_ = false;

	// FOR TESTING
	Sprite *test;

	//provisional
	//se instancia en clase Game.h y se gestiona render, update y hangleEvent de los estados en pila 
	GameStateMachine* gmStMachine_;
};

