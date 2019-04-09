#include "MainMenuState.h"
#include "Reticule.h"



MainMenuState::MainMenuState()
{
	Game::getInstance ()->getCamera (GAME_CAMERA)->setZoom (1.0, false);
	Game::getInstance ()->getCamera (UI_CAMERA)->setZoom (1.0, false);

	//inicialiacion id sonidos - se usa para gestionar el SoundManager desde MouseClickIC
	Sound_NewGameButton_ = CLIC_BUTTON_NEWGAME;

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
	//MAIN MENU TITLE
	mainBackground_ = new Container();
	mainBackground_->setPosition(Vector2D(MAIN_TITLE[texAnm].pos.x, MAIN_TITLE[texAnm].pos.y));
	mainBackground_->setWidth(Game::getInstance()->getCameraWidth());
	mainBackground_->setHeight(Game::getInstance()->getCameraHeight());
	//animation
	mainTitleAnm_ = new Animation();
	mainTitleAnm_->loadAnimation(MAIN_TITLE[title_defaultAnm].idlePath, MAIN_TITLE[title_defaultAnm].name, MAIN_TITLE[title_defaultAnm].frAnm.cols, MAIN_TITLE[title_defaultAnm].frAnm.rows);
	mainTitleAnm_->loadAnimation(MAIN_TITLE[texAnm].idlePath, MAIN_TITLE[texAnm].name, MAIN_TITLE[texAnm].frAnm.cols, MAIN_TITLE[texAnm].frAnm.rows);
	mainBackground_->addRenderComponent(mainTitleAnm_);


	//BUTTONS
	buttons_["newGameButton"] = new Button(mainStateCallback, (NEW_GAME_BUTTON), Sound_NewGameButton_);
	buttons_["extiButton"] = new Button(exitGameCallback, (EXIT_BUTTON));

	buttons_["newGameButton"]->setPosition(Vector2D(NEW_GAME_BUTTON[defaultAnm].pos.x, NEW_GAME_BUTTON[defaultAnm].pos.y));
	buttons_["newGameButton"]->setWidth(500);
	buttons_["newGameButton"]->setHeight(200);
	buttons_["extiButton"]->setPosition(Vector2D(EXIT_BUTTON[defaultAnm].pos.x, EXIT_BUTTON[defaultAnm].pos.y));
	buttons_["extiButton"]->setWidth(250);
	buttons_["extiButton"]->setHeight(150);


	//reticule
	Reticule::GetInstance()->ChangeReticule("gun");

	//Container to GO list
	stage_.push_back(mainBackground_);
	stage_.push_back(buttons_["newGameButton"]);
	stage_.push_back(buttons_["extiButton"]);
	stage_.push_back(Reticule::GetInstance());


	//gestion de la escena
	//buttons_["newGameButton"]->setActive(false);
	//buttons_["extiButton"]->setActive(false);
	mainTitleAnm_->playAnimation(MAIN_TITLE[texAnm].name, 6.0f, false);
	Game::getInstance()->getSoundManager()->playMusic(MAIN_THEME_MUSIC, -1);
	Game::getInstance()->getSoundManager()->playSound(TAXI_START, 0);
}

void MainMenuState::update (Uint32 deltaTime) {
	Game::getInstance ()->getCamera (GAME_CAMERA)->setCentered (false);
	Game::getInstance ()->getCamera (UI_CAMERA)->setCentered (false);


	if (!mainTitleAnm_->isAnimationPlaying(MAIN_TITLE[texAnm].name)) {
		mainTitleAnm_->stopAnimation();
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


