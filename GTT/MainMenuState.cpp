#include "MainMenuState.h"
#include "Reticule.h"



MainMenuState::MainMenuState()
{
	Game::getInstance ()->getCamera (GAME_CAMERA)->setZoom (1.0, false);
	Game::getInstance ()->getCamera (UI_CAMERA)->setZoom (1.0, false);


	//inicialización buttons - se insertan en el map
	buttons_["newGameButton"] = new Button(mainStateCallback, NEW_GAME_BUTTON);

	//se añade el container a la lista de GO
	stage_.push_back(buttons_["newGameButton"]);

	//newGameButton_ = new Button(mainStateCallback, NEW_GAME_BUTTON);
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
	
	if (!(buttons_["newGameButton"]->getButtonAnimacion()->isAnimationPlaying(NEW_GAME_BUTTON.name[clickButton])) && buttons_["newGameButton"]->isMouseClickICEvent()) {
		int i = 0;
		mainStateCallback();
	}

	GameState::update (deltaTime);
}


