#include "Game.h"
#include "Camera.h"
#include <iostream>
#include "Vehicle.h"
#include "SoundManager.h"


using namespace std;

// Static initializations
SDL_Window* Game::window_ = nullptr;
SDL_Renderer* Game::renderer_ = nullptr;
SoundManager* Game::soundManager_ = nullptr;
map<cameraType, Camera*> Game::cameras_ = map<cameraType, Camera*>();
b2World* Game::world_ = nullptr;

Game::Game(SDL_Window *window_, SDL_Renderer *renderer_) {
	Game::window_ = window_;
	Game::renderer_ = renderer_;
	Game::soundManager_ = new SoundManager();

	// SOUND MANAGER TEST
	Game::getSoundManager()->loadSound("../Assets/sounds/default.wav", "default");

	// PHYSICS TEST
	world_ = new b2World(b2Vec2(0, 9));
	cameras_[GAME_CAMERA] = new Camera(1600, 900);
	taxi_ = new Vehicle();
	taxi_->setWidth(400);
	taxi_->setHeight(400);
}

Game::~Game() {

}

/*-----------------------------------------------------------------------*/

bool Game::handleEvents(Uint32 deltaTime) {
	SDL_Event event;

	while (SDL_PollEvent(&event) && !exit_) {
		// LLamar a los handleEvent() de los GameObjects
		if (event.type == SDL_QUIT) exit_ = true;
		if (event.type == SDL_KEYDOWN) Game::soundManager_->playSound("default");
	}

	return exit_;
}
bool Game::update(Uint32 deltaTime) {
	taxi_->update(deltaTime);
	Game::world_->Step((float) deltaTime / 1000, 8, 3);
	// LLamar a los update() de los GameObjects
	return exit_;
}
void Game::render(Uint32 deltaTime) {
	taxi_->render(deltaTime);
	// LLamar a los render() de los GameObjects
}

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

b2World * Game::GetWorld()
{
	return world_;
}

SoundManager * Game::getSoundManager() {
	return soundManager_;
}


/*-----------------------------------------------------------------------*/