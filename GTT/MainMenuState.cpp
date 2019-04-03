#include "MainMenuState.h"
#include "Reticule.h"



MainMenuState::MainMenuState()
{
	Game::getInstance ()->getCamera (GAME_CAMERA)->setZoom (1.0, false);
	Game::getInstance ()->getCamera (UI_CAMERA)->setZoom (1.0, false);


	//inicialización buttons
	newGameButton_ = new Button(mainStateCallback, NEW_GAME_BUTTON);
	stage_.push_back(newGameButton_);

	//stage_.push_back (new Button (exitGameCallback, EXIT_GAME_BUTTON));

	//reticule
	Reticule::GetInstance()->ChangeReticule("gun");
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
