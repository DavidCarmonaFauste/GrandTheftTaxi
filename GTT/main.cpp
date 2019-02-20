#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <SDL_mixer.h>
#include <iostream>

#include "Game.h"

using namespace std;

typedef unsigned int uint;

int main(int argc, char* argv[]) {

	// Initialization values
	SDL_Window* window_ = nullptr;
	SDL_Renderer* renderer_ = nullptr;
	const int winWidth_ = 1280;
	const int winHeight_ = 720;
	int winX_, winY_;
	winX_ = winY_ = SDL_WINDOWPOS_CENTERED;

	// SDL initialization
	SDL_Init(SDL_INIT_EVERYTHING);
	window_ = SDL_CreateWindow("Grand Theft Taxi", winX_, winY_,
							  winWidth_, winHeight_, SDL_WINDOW_SHOWN);
	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
	SDL_RenderSetLogicalSize(renderer_, 1600, 900);

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
		return -1;

	// Check for errors
	if (window_ == nullptr || renderer_ == nullptr) {
		cout << "SDL initialization failed\n";
		return -1;
	}

	// Create and run the game
	Game* game_ = new Game(window_, renderer_);
	double lastTime = SDL_GetTicks();
	double deltaTime = lastTime;

	//bool exit = game->update(deltaTime);
	bool exit = false;

	while (!exit) {
		SDL_RenderClear(renderer_);
		// Game cycle
		
		game_->handleEvents(deltaTime);
		exit = game_->update(deltaTime);
		game_->render(deltaTime);
		SDL_RenderPresent(renderer_);

		// Update the delta time
		deltaTime = SDL_GetTicks() - lastTime;
		lastTime = SDL_GetTicks();

		//run gestiona render, update y handleEvent dependiendo del estado. 
		//game_->run(deltaTime);
		//la ruptura se define mediante el m�todo propio de game_
		//exit = game_->exitGame();
	}

	// Cleaning
	delete game_;

	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
	SDL_Quit();
	
	return 0;
}