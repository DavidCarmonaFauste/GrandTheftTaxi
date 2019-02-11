#include "Game.h"
#include "Sprite.h"

using namespace std;

// Static initializations
SDL_Window* Game::window_ = nullptr;
SDL_Renderer* Game::renderer_ = nullptr;

Game::Game(SDL_Window *window_, SDL_Renderer *renderer_) {
	Game::window_ = window_;
	Game::renderer_ = renderer_;
}

Game::~Game() {

}

bool Game::update(double deltaTime) {
	handleEvents();

	return exit;
}

void Game::handleEvents() {
	SDL_Event event;

	while (SDL_PollEvent(&event) && !exit) {
		if (event.type == SDL_QUIT) exit_ = true;
	
	}
}
