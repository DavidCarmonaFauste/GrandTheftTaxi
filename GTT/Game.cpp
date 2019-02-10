#include "Game.h"
#include "Sprite.h"

using namespace std;

// Static initializations
SDL_Window* Game::window = nullptr;
SDL_Renderer* Game::renderer = nullptr;

Game::Game(SDL_Window *window_, SDL_Renderer *renderer_) {
	Game::window = window_;
	Game::renderer = renderer_;



	// FOR TESTING
	test = new Sprite();
	test->loadAnimation("./../Assets/sprites/test_animation.png", "test", 8, 2);
	test->playAnimation("test", 10);
}

Game::~Game() {

}

bool Game::update(double deltaTime) {
	test->update(deltaTime);

	handleEvents();

	return exit;
}

void Game::handleEvents() {
	SDL_Event event;

	while (SDL_PollEvent(&event) && !exit) {
		if (event.type == SDL_QUIT) exit = true;
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_p) test->pauseAnimation();
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_s) test->stopAnimation();
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_r) test->resumeAnimation();
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_y) test->playAnimation("test", 10);
	}
}
