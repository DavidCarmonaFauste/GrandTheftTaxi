#include "Game.h"
#include "Camera.h"
#include <iostream>
#include "Vehicle.h"
#include "SoundManager.h"
#include "TileMap.h"
#include "Respawner.h"
#include "Gun.h"
#include "ShootIC.h"
#include "ProyectilePool.h"
#include "ShotGun.h"
#include "Reticule.h"


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

	// World and cameras
	world_ = new b2World(b2Vec2(0, 10));
	cameras_[GAME_CAMERA] = new Camera(1280, 720);

	// Taxi
	taxi_ = new Vehicle(Resources::Taxi);
	taxi_->addInputComponent(new ShootIC());
	gun_ = new Gun();
	shotgun_ = new ShotGun();

	taxi_->EquipTurret(shotgun_);

	//taxi_->EquipTurret(gun_);

	// Respawn system
	GameObject* initialRespawnPoint = new Container();
	initialRespawnPoint->setPosition(Vector2D(0, 0));

	Respawner *respawner = new Respawner(taxi_->getHealthComponent());
	respawner->addRespawnPoint(initialRespawnPoint, "initial");
	taxi_->addLogicComponent(respawner);

	// TESTING TILEMAP
	tileMap_ = new TileMap("../Assets/maps/test.tmx");
	SDL_ShowCursor(0);

}

Game::~Game() {

}

/*-----------------------------------------------------------------------*/

bool Game::handleEvents(Uint32 deltaTime) {
	SDL_Event e;


	while (SDL_PollEvent(&e) && !exit_) {
		// LLamar a los handleEvent() de los GameObjects
		if (e.type == SDL_KEYDOWN) {
			switch (e.key.keysym.sym) {
			case SDLK_ESCAPE:
				exit_ = true;
				break;
				// Pressing f to toggle fullscreen.
			case SDLK_f:
				int flags = SDL_GetWindowFlags(window_);
				if (flags & SDL_WINDOW_FULLSCREEN) {
					SDL_SetWindowFullscreen(window_, 0);
				}
				else {
					SDL_SetWindowFullscreen(window_, SDL_WINDOW_FULLSCREEN);
				}
				break;
			}
		}
		taxi_->handleInput(deltaTime, e);
		if (e.type == SDL_QUIT) exit_ = true;
	}

	return exit_;
}
bool Game::update(Uint32 deltaTime) {
	taxi_->update(deltaTime);
	tileMap_->update(deltaTime);
	ProyectilePool::GetInstance()->update(deltaTime);
	Reticule::GetInstance()->update(deltaTime);
	Game::world_->Step((float) deltaTime / 1000, 8, 3);

	// LLamar a los update() de los GameObjects
	return exit_;
}
void Game::render(Uint32 deltaTime) {
	tileMap_->render(deltaTime);
	ProyectilePool::GetInstance()->render(deltaTime);
	taxi_->render(deltaTime);
	Reticule::GetInstance()->render(deltaTime);

	
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