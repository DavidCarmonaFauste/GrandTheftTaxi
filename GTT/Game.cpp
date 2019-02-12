#include "Game.h"
#include "Sprite.h"

using namespace std;

// Static initializations
SDL_Window* Game::window = nullptr;
SDL_Renderer* Game::renderer = nullptr;

Game::Game(SDL_Window *window_, SDL_Renderer *renderer_) {
	Game::window = window_;
	Game::renderer = renderer_;
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
		if (event.type == SDL_QUIT) exit = true;
	}
}
