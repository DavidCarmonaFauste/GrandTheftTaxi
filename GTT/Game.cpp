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

Game::Game(SDL_Window *window, SDL_Renderer *renderer) {
	Game::window_ = window;
	Game::renderer_ = renderer;

	cameras_[GAME_CAMERA] = new Camera(1600, 900);

	//videoIntro_ = new VideoState("\YuzuGames_Intro.mp4.avi");
	//videoIntro_->videoInit();
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
/*bool Game::update(Uint32 deltaTime) {
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
	handleEvents(deltaTime);
	gmStMachine_->render(deltaTime);
	gmStMachine_->get_CurrentState()->update(deltaTime);
}

//exitGame devuelve el valor del atributo, determina la ruptura del bucle en Main.cpp
bool Game::exitGame() {
	return exit_;
}


/*-----------------------------------------------------------------------*/