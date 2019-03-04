#include "Game.h"
#include "Camera.h"
#include <iostream>
#include "Sprite.h"
#include "GameStateMachine.h"
#include "VideoState.h"


using namespace std;

// Static initializations
SDL_Window* Game::window_ = nullptr;
SDL_Renderer* Game::renderer_ = nullptr;
map<cameraType, Camera*> Game::cameras_ = map<cameraType, Camera*>();

Game* Game::singleton = nullptr;
Game::Game() {
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

	// Check for errors
	if (window_ == nullptr || renderer_ == nullptr) {
		cout << "SDL initialization failed\n";
	}

	cameras_[GAME_CAMERA] = new Camera(1600, 900);


	gmStMachine_ = new GameStateMachine();
}

Game::~Game() {

}

/*-----------------------------------------------------------------------*/

//los eventos los gestiona la aplicación. Conecta directamente con handleEvents del estado actual. 
 void Game::handleEvents(Uint32 deltaTime) {
	SDL_Event event;

	while (SDL_PollEvent(&event) && !exit_) {
		gmStMachine_->get_CurrentState()->handleEvents(deltaTime, event);
		if (event.type == SDL_QUIT) exit_ = true; //exit_ comunica con main a través del método exitGame
	}
}
 void Game::update(Uint32 deltaTime)
 {
	 gmStMachine_->get_CurrentState()->update(deltaTime);
 }
 void Game::render(Uint32 deltaTime)
 {
	 SDL_RenderClear(renderer_);
	 gmStMachine_->get_CurrentState()->render(deltaTime);
	 SDL_RenderPresent(renderer_);
 }

 Game * Game::getInstance() {
	 if (singleton == nullptr)
		 singleton = new Game();

	 return singleton;
 }

 //Run es llamado desde Main y gestiona los update, render y hangleEvents de los estados
void Game::run() {
	double lastTime = SDL_GetTicks();
	double deltaTime = lastTime;

	while (!exit_) {
		handleEvents(deltaTime);
		update(deltaTime);
		render(deltaTime);

		// Update the delta time
		deltaTime = SDL_GetTicks() - lastTime;
		lastTime = SDL_GetTicks();
	}

	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
	SDL_Quit();	
}

//exitGame devuelve el valor del atributo, determina la ruptura del bucle en Main.cpp
bool Game::exitGame() {
	return exit_;
}
