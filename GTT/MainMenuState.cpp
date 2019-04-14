#include "MainMenuState.h"
#include "Reticule.h"
#include "MouseClickIC.h"


MainMenuState::MainMenuState()
{
	//inicialiacion id sonidos - se usa para gestionar el SoundManager desde MouseClickIC
	Sound_NewGameButton_ = CLIC_BUTTON_NEWGAME;
	cont_1 = -1;
}


MainMenuState::~MainMenuState()
{
	while (!stage_.empty ()) {
		delete stage_.back (); 
		stage_.back () = nullptr;
		stage_.pop_back ();
	}

}

void MainMenuState::start()
{
	Game::getInstance()->getCamera(GAME_CAMERA)->setZoom(1.0, false);
	Game::getInstance()->getCamera(UI_CAMERA)->setZoom(1.0, false);


	//MAIN MENU TITLE
	mainBackground_ = new Container();
	mainBackground_->setPosition(Vector2D(MAIN_TITLE.pos.x, MAIN_TITLE.pos.y));
	mainBackground_->setWidth(Game::getInstance()->getCameraWidth());
	mainBackground_->setHeight(Game::getInstance()->getCameraHeight());
		//animation
	Animation* mainTitleAnm_ = new Animation();
	mainTitleAnm_->loadAnimation(MAIN_TITLE.idlePath, MAIN_TITLE.name, MAIN_TITLE.frAnm.cols, MAIN_TITLE.frAnm.rows);
	mainBackground_->addRenderComponent(mainTitleAnm_);
	mainTitleAnm_->setAnimation(MAIN_TITLE.name);


	//BUTTONS
		//build
	buttons_["newGameButton"] = new Button(mainStateCallback);
	buttons_["extiButton"] = new Button(exitGameCallback);
		//set atributtes
	buttons_["newGameButton"]->setPosition(Vector2D(NEW_GAME_BUTTON[defaultAnm].pos.x, NEW_GAME_BUTTON[defaultAnm].pos.y));
	buttons_["newGameButton"]->setWidth(250);
	buttons_["newGameButton"]->setHeight(150);
	buttons_["extiButton"]->setPosition(Vector2D(EXIT_BUTTON[defaultAnm].pos.x, EXIT_BUTTON[defaultAnm].pos.y));
	buttons_["extiButton"]->setWidth(250);
	buttons_["extiButton"]->setHeight(150);
		//build and set private components
			//inputC
	MouseClickIC* mCIc = new MouseClickIC(NEW_GAME_BUTTON); //NEW GAME BUTTON
	buttons_["newGameButton"]->setMouseClickIC(mCIc);
	buttons_["newGameButton"]->addInputComponent(mCIc);
	MouseClickIC* mCIc_2 = new MouseClickIC(EXIT_BUTTON); //EXIT BUTTON
	buttons_["extiButton"]->setMouseClickIC(mCIc_2);
	buttons_["extiButton"]->addInputComponent(mCIc_2);
			//sounds
	soundId sound = CLIC_BUTTON_NEWGAME;
	buttons_["newGameButton"]->setClickSound(sound);
	buttons_["extiButton"]->setClickSound();
			//renderC - 
	Animation* newG_Animation = new Animation(); //NEW GAME BUTTON
			//first animation is the last to insert
	newG_Animation->loadAnimation(NEW_GAME_BUTTON[clickButton].idlePath, NEW_GAME_BUTTON[clickButton].name, NEW_GAME_BUTTON[clickButton].frAnm.cols, NEW_GAME_BUTTON[clickButton].frAnm.rows);
	newG_Animation->loadAnimation(NEW_GAME_BUTTON[overButton].idlePath, NEW_GAME_BUTTON[overButton].name, NEW_GAME_BUTTON[overButton].frAnm.cols, NEW_GAME_BUTTON[overButton].frAnm.rows);
	newG_Animation->loadAnimation(NEW_GAME_BUTTON[defaultAnm].idlePath, NEW_GAME_BUTTON[defaultAnm].name, NEW_GAME_BUTTON[defaultAnm].frAnm.cols, NEW_GAME_BUTTON[defaultAnm].frAnm.rows);
			//add and set renderC
	buttons_["newGameButton"]->addRenderComponent(newG_Animation);
	buttons_["newGameButton"]->setButtonAnimation(newG_Animation);
	
	Animation* exitG_Animation = new Animation(); //EXIT BUTTON
		//first animation is the last to insert
	exitG_Animation->loadAnimation(EXIT_BUTTON[defaultAnm].idlePath, EXIT_BUTTON[defaultAnm].name, EXIT_BUTTON[defaultAnm].frAnm.cols, EXIT_BUTTON[defaultAnm].frAnm.rows);
	exitG_Animation->loadAnimation(EXIT_BUTTON[overButton].idlePath, EXIT_BUTTON[overButton].name, EXIT_BUTTON[overButton].frAnm.cols, EXIT_BUTTON[overButton].frAnm.rows);
		//add and set renderC
	buttons_["extiButton"]->addRenderComponent(exitG_Animation);
	buttons_["extiButton"]->setButtonAnimation(exitG_Animation);
	
	

	//Reticule
	Reticule::GetInstance()->ChangeReticule("gun");

	
	//Taxi
	mainTitle_Taxi_ = new Container();
	mainTitle_Taxi_->setPosition(Vector2D(MAIN_TITLE_TAXI.pos.x, MAIN_TITLE_TAXI.pos.y));
	mainTitle_Taxi_->setWidth(293);
	mainTitle_Taxi_->setHeight(244);
		//animation
	mainTitle_Taxi_anm = new Animation();
		//taxAnm
	mainTitle_Taxi_anm->loadAnimation(MAIN_TITLE_TAXI_ANM.idlePath, MAIN_TITLE_TAXI_ANM.name, MAIN_TITLE_TAXI_ANM.frAnm.cols, MAIN_TITLE_TAXI_ANM.frAnm.rows);
		//default
	mainTitle_Taxi_anm->loadAnimation(MAIN_TITLE_TAXI.idlePath, MAIN_TITLE_TAXI.name, MAIN_TITLE_TAXI.frAnm.cols, MAIN_TITLE_TAXI.frAnm.rows);
		//add and set renderC
	mainTitle_Taxi_->addRenderComponent(mainTitle_Taxi_anm);
	mainTitle_Taxi_anm->setAnimation(MAIN_TITLE_TAXI.name);


	//Container to GameObj list
	stage_.push_back(mainBackground_);
	stage_.push_back(buttons_["newGameButton"]);
	stage_.push_back(buttons_["extiButton"]);
	stage_.push_back(Reticule::GetInstance());
	stage_.push_back(mainTitle_Taxi_);


	//scene management
	Game::getInstance()->getSoundManager()->playMusic(MAIN_THEME_MUSIC, -1); //MainTitle Theme
	Game::getInstance()->getSoundManager()->playSound(TAXI_START, 0);	//vehicle start sound
}

void MainMenuState::update (Uint32 deltaTime) {
	Game::getInstance ()->getCamera (GAME_CAMERA)->setCentered (false);
	Game::getInstance ()->getCamera (UI_CAMERA)->setCentered (false);

	//!vehicle start sound
	if (cont_1 == -1 && !(Game::getInstance()->getSoundManager()->isSoundPlaying(-1))) {
		mainTitle_Taxi_anm->setAnimation(MAIN_TITLE_TAXI_ANM.name);
		cont_1 = 1;
	}
	
	if (!(buttons_["newGameButton"]->getButtonAnimacion()->isAnimationPlaying(NEW_GAME_BUTTON[clickButton].name)) && buttons_["newGameButton"]->isMouseClickICEvent()) {
		Game::getInstance()->getSoundManager()->pauseMusic();
		Game::getInstance()->getSoundManager()->pauseSound(-1);
		mainStateCallback();
	}
	else if (!(buttons_["extiButton"]->getButtonAnimacion()->isAnimationPlaying(NEW_GAME_BUTTON[clickButton].name)) && buttons_["extiButton"]->isMouseClickICEvent()) {
		Game::getInstance()->getSoundManager()->pauseMusic();
		Game::getInstance()->getSoundManager()->pauseSound(-1);
		exitGameCallback();
	}

	GameState::update (deltaTime);


}


