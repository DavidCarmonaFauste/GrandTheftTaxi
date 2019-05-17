#include "GameOverMenu.h"
#include "Reticule.h"
#include "Game.h"


GameOverMenu::GameOverMenu()
{
}


GameOverMenu::~GameOverMenu()
{
	delete background_; background_ = nullptr;
	delete blackBackground_; blackBackground_ = nullptr;
	delete backgroundSprite_;
	delete blackBackgoundSprite_;
	delete backSprite_;

	for (auto button : buttons_) {
		delete button.second; button.second = nullptr;
	}
	buttons_.clear();
}


void GameOverMenu::start() {
	int i; //recoge el valor del index si el elemento est? en el vector
	if (!isRegistered(this, i))
		registerObserver(this);

	Game::getInstance()->getCamera(GAME_CAMERA)->setZoom(1.0, false);
	Game::getInstance()->getCamera(UI_CAMERA)->setZoom(1.0, false);

	// BACKGROUND
	setBackground();

	// BUTTONS
	setButtons();
	setButtonComponents();


	//Container to GameObj list
	stage_.push_back(background_);
	//stage_.push_back(blackBackground_);
	stage_.push_back(buttons_["backButton"]);
	stage_.push_back(Reticule::getInstance());
}


void GameOverMenu::end() {
}

void GameOverMenu::updateState()
{
	
}


void GameOverMenu::update(Uint32 deltaTime) {
	Game::getInstance()->getCamera(GAME_CAMERA)->setCentered(false);
	Game::getInstance()->getCamera(UI_CAMERA)->setCentered(false);

	GameState::update(deltaTime);
}


bool GameOverMenu::receiveEvent(Event & e) {
	switch (e.type_)
	{
	case CLICK_BUTTON: {
		MouseClickLeft  MouseClickLeft_ = static_cast<MouseClickLeft&>(e);
	if (MouseClickLeft_.button_ == buttons_["backButton"]->getIndex()) {
			
			//updateState();
			Game::getInstance()->getGameStateMachine()->fromGameOverMenuToMainMenu();
		}
		break;
	}
	default:
		break;
	}
	return true;
}


void GameOverMenu::setBackground() {
	//Global background
	backgroundSprite_ = new Sprite(GAS_BACKGROUND_INFO.idlePath, GAS_BACKGROUND_INFO.width, GAS_BACKGROUND_INFO.height);
	background_ = new Container();

	background_->setWidth(GAS_BACKGROUND_W);
	background_->setHeight(GAS_BACKGROUND_H);
	background_->setPosition (Vector2D (0, 0));
	background_->addRenderComponent(backgroundSprite_);
}


void GameOverMenu::setButtons() {
	// build
	buttons_["backButton"] = new Button();
	buttons_["backButton"]->getMouseClickIC()->registerObserver(this);

	// set
	buttons_["backButton"]->setPosition(BACK_BUTTON_POSITION);
	buttons_["backButton"]->setWidth(BACK_BUTTON_INFO.width);
	buttons_["backButton"]->setHeight(BACK_BUTTON_INFO.height);
	buttons_["backButton"]->setIndex(1);

}


void GameOverMenu::setButtonComponents() {
	backSprite_ = new Sprite(BACK_BUTTON_INFO.idlePath, BACK_BUTTON_INFO.width, BACK_BUTTON_INFO.height, BACK_BUTTON_POSITION.x, BACK_BUTTON_POSITION.y);

	buttons_["backButton"]->addRenderComponent(backSprite_);
}

