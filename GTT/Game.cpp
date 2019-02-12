#include "Game.h"
#include "Animation.h"

using namespace std;

// Static initializations
SDL_Window* Game::window_ = nullptr;
SDL_Renderer* Game::renderer_ = nullptr;

Game::Game(SDL_Window *window_, SDL_Renderer *renderer_) {
	Game::window_ = window_;
	Game::renderer_ = renderer_;

	test = new Animation();
	test->loadAnimation("./../Assets/sprites/test_animation.png", "test", 8, 2);
	test->playAnimation("test", 10);
}

Game::~Game() {

}

void Game::handleEvents(Uint32 deltaTime) {
	SDL_Event event;

	while (SDL_PollEvent(&event) && !exit) {
		// LLamar a los handleEvent() de los GameObjects
		if (event.type == SDL_QUIT) exit_ = true;
	}
}

bool Game::update(Uint32 deltaTime) {
	// LLamar a los update() de los GameObjects

	return exit_;
}

void Game::render(Uint32 deltaTime) {
	// LLamar a los render() de los GameObjects
	test->render(deltaTime);
}
