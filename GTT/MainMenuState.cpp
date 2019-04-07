#include "MainMenuState.h"
#include "Reticule.h"



MainMenuState::MainMenuState()
{
	Game::getInstance ()->getCamera (GAME_CAMERA)->setZoom (1.0, false);
	Game::getInstance ()->getCamera (UI_CAMERA)->setZoom (1.0, false);

	//inicialiacio id sonidos - se usa para gestionar el SoundManager desde MouseClickIC
	Sound_NewGameButton_ = TAXI_ACCELERATE_01;

	//inicialización buttons - se insertan en el map
	buttons_["newGameButton"] = new Button(mainStateCallback, (NEW_GAME_BUTTON), Sound_NewGameButton_);
	buttons_["extiButton"] = new Button(exitGameCallback, (EXIT_BUTTON));

	//se añade el container a la lista de GO
	stage_.push_back(buttons_["newGameButton"]);
	stage_.push_back(buttons_["extiButton"]);


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
	
	if (!(buttons_["newGameButton"]->getButtonAnimacion()->isAnimationPlaying(NEW_GAME_BUTTON[clickButton].name)) && buttons_["newGameButton"]->isMouseClickICEvent()) {
		int i = 0;
		mainStateCallback();
	}
	else if (!(buttons_["extiButton"]->getButtonAnimacion()->isAnimationPlaying(NEW_GAME_BUTTON[clickButton].name)) && buttons_["extiButton"]->isMouseClickICEvent()) {
		int i = 0;
		exitGameCallback();
	}

	GameState::update (deltaTime);
}


