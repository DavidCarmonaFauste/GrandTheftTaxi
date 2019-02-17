#include "Game.h"
#include "Camera.h"
#include <iostream>
#include "Sprite.h"

using namespace std;

// Static initializations
SDL_Window* Game::window_ = nullptr;
SDL_Renderer* Game::renderer_ = nullptr;
map<cameraType, Camera*> Game::cameras_ = map<cameraType, Camera*>();

Game::Game(SDL_Window *window_, SDL_Renderer *renderer_) {
	Game::window_ = window_;
	Game::renderer_ = renderer_;

	cameras_[GAME_CAMERA] = new Camera(1600, 900);
}

Game::~Game() {

}

/*-----------------------------------------------------------------------*/

/*void Game::handleEvents(Uint32 deltaTime) {
	SDL_Event event;

	while (SDL_PollEvent(&event) && !exit_) {
		// LLamar a los handleEvent() de los GameObjects
		if (event.type == SDL_QUIT) exit_ = true;
	}

	return exit_;
}
bool Game::update(Uint32 deltaTime) {
	// LLamar a los update() de los GameObjects
	return exit_;
}
void Game::render(Uint32 deltaTime) {
	// LLamar a los render() de los GameObjects
}*/

/*-----------------------------------------------------------------------*/
//provisonal. 

//Run es llamado desde Main y gestiona los update, render y hangleEvents de los estados
void Game::run(uint deltaTime) {
	gmStMachine_->handleEvents(deltaTime);
	gmStMachine_->render(deltaTime);
	//falta gmStMachine_->update(deltaTime);
}

//exitGame devuelve el valor del atributo, determina la ruptura del bucle en Main.cpp
bool Game::exitGame() {
	return exit_;
}


/*-----------------------------------------------------------------------*/