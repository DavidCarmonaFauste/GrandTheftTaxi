
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>

#include "Game.h"

using namespace std;

int main(int argc, char* argv[]){
	// Initialization values
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	const int winWidth = 800;
	const int winHeight = 600;
	int winX, winY;
	winX = winY = SDL_WINDOWPOS_CENTERED;

	// SDL initialization
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Grand Theft Taxi", winX, winY,
							  winWidth, winHeight, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	// Check for errors
	if (window == nullptr || renderer == nullptr) {
		cout << "SDL initialization failed\n";
		return -1;
	}

	// Create and run the game
	Game* game = new Game(window, renderer);
	double lastTime = SDL_GetTicks();
	double deltaTime = lastTime;

	bool exit = game->update(deltaTime);
	while (!exit) {
		SDL_RenderClear(renderer);
		exit = game->update(deltaTime);
		SDL_RenderPresent(renderer);
		
		// Update the delta time
		deltaTime = SDL_GetTicks() - lastTime;
		lastTime = SDL_GetTicks();
	}

	// Cleaning
	delete game;

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}