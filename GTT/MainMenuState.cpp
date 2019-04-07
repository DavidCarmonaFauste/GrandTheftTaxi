#include "MainMenuState.h"
#include "Reticule.h"



MainMenuState::MainMenuState()
{
	Game::getInstance ()->getCamera (GAME_CAMERA)->setZoom (1.0, false);
	Game::getInstance ()->getCamera (UI_CAMERA)->setZoom (1.0, false);

	stage_.push_back (new Button (mainStateCallback, MainMenuPlay));
	stage_.push_back (new Button (exitGameCallback, MainMenuExit));
	stage_.push_back(Reticule::GetInstance());
}


MainMenuState::~MainMenuState()
{
	while (!stage_.empty ()) {
		delete stage_.back (); 
		stage_.back () = nullptr;
		stage_.pop_back ();
	}

}

void MainMenuState::update (Uint32 deltaTime) {
	Game::getInstance ()->getCamera (GAME_CAMERA)->setCentered (false);
	Game::getInstance ()->getCamera (UI_CAMERA)->setCentered (false);

	GameState::update (deltaTime);
}
