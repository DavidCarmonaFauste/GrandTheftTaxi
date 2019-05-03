#include "GasFillMenu.h"
#include "Reticule.h"
#include "Game.h"
#include "Vehicle.h"


GasFillMenu::GasFillMenu () {
}


GasFillMenu::~GasFillMenu () {
	while (!stage_.empty()) {
		delete stage_.back();
		stage_.back() = nullptr;
		stage_.pop_back();
	}

	delete backgroundSprite_;
	delete fill_5_Sprite_;
	delete fill_10_Sprite_;
	delete fill_25_Sprite_;
	delete backSprite_;
}


void GasFillMenu::start () {
	int i; //recoge el valor del index si el elemento está en el vector
	if (!isRegistered(this, i))
		registerObserver(this);

	Game::getInstance()->getCamera(GAME_CAMERA)->setZoom(1.0, false);
	Game::getInstance()->getCamera(UI_CAMERA)->setZoom(1.0, false);
	
	// BACKGROUND
	setBackground ();

	// BUTTONS
	setButtons ();
	setButtonComponents ();

	
	//Container to GameObj list
	stage_.push_back(background_);
	stage_.push_back(buttons_["fill_5_Button"]);
	stage_.push_back(buttons_["fill_10_Button"]);
	stage_.push_back(buttons_["fill_25_Button"]);
	stage_.push_back(buttons_["backButton"]);
	stage_.push_back(Reticule::getInstance());
}


void GasFillMenu::end () {
}


void GasFillMenu::update (Uint32 deltaTime) {
	Game::getInstance()->getCamera(GAME_CAMERA)->setCentered(false);
	Game::getInstance()->getCamera(UI_CAMERA)->setCentered(false);

	GameState::update(deltaTime);
}


bool GasFillMenu::receiveEvent (Event & e) {
	switch (e.type_)
	{
	case CLICK_BUTTON: {
		MouseClickLeft  MouseClickLeft_ = static_cast<MouseClickLeft&>(e);

		if (MouseClickLeft_.button_ == buttons_["fill_5_Button"]->getIndex()) {
			cout << "fill 5%\n";
		}
		else if (MouseClickLeft_.button_ == buttons_["fill_10_Button"]->getIndex ()) {
			cout << "fill 10%\n";
		}
		else if (MouseClickLeft_.button_ == buttons_["fill_25_Button"]->getIndex ()) {
			cout << "fill 25%\n";
		}
		else if (MouseClickLeft_.button_ == buttons_["backButton"]->getIndex ()) {
			Game::getInstance ()->getGameStateMachine ()->fromFillMenuToGasMainMenu ();
		}
		break;
	}
	default:
		break;
	}
	return true;
}


void GasFillMenu::setBackground () {
	backgroundSprite_ = new Sprite (GAS_BACKGROUND_INFO.idlePath, GAS_BACKGROUND_INFO.width, GAS_BACKGROUND_INFO.height);
	
	background_ = new Container ();

	background_->setWidth (GAS_BACKGROUND_W);
	background_->setHeight (GAS_BACKGROUND_H);
	background_->addRenderComponent (backgroundSprite_);
}


void GasFillMenu::setButtons () {
	// build
	buttons_["fill_5_Button"] = new Button();
	buttons_["fill_5_Button"]->getMouseClickIC()->registerObserver(this);
	buttons_["fill_10_Button"] = new Button();
	buttons_["fill_10_Button"]->getMouseClickIC()->registerObserver(this);
	buttons_["fill_25_Button"] = new Button();
	buttons_["fill_25_Button"]->getMouseClickIC()->registerObserver(this);
	buttons_["backButton"] = new Button();
	buttons_["backButton"]->getMouseClickIC()->registerObserver(this);

	// set
	buttons_["fill_5_Button"]->setPosition(GAS_5_BUTTON_POSITION);
	buttons_["fill_5_Button"]->setWidth(GAS_5_BUTTON_INFO.width);
	buttons_["fill_5_Button"]->setHeight(GAS_5_BUTTON_INFO.height);
	buttons_["fill_5_Button"]->setIndex(1);

	buttons_["fill_10_Button"]->setPosition(GAS_10_BUTTON_POSITION);
	buttons_["fill_10_Button"]->setWidth(GAS_10_BUTTON_INFO.width);
	buttons_["fill_10_Button"]->setHeight(GAS_10_BUTTON_INFO.height);
	buttons_["fill_10_Button"]->setIndex(2);

	buttons_["fill_25_Button"]->setPosition(GAS_25_BUTTON_POSITION);
	buttons_["fill_25_Button"]->setWidth(GAS_25_BUTTON_INFO.width);
	buttons_["fill_25_Button"]->setHeight(GAS_25_BUTTON_INFO.height);
	buttons_["fill_25_Button"]->setIndex(3);

	buttons_["backButton"]->setPosition(BACK_BUTTON_POSITION);
	buttons_["backButton"]->setWidth(BACK_BUTTON_INFO.width);
	buttons_["backButton"]->setHeight(BACK_BUTTON_INFO.height);
	buttons_["backButton"]->setIndex(4);
}


void GasFillMenu::setButtonComponents () {
	fill_5_Sprite_ = new Sprite (GAS_5_BUTTON_INFO.idlePath, GAS_5_BUTTON_INFO.width, GAS_5_BUTTON_INFO.height, GAS_5_BUTTON_POSITION.x, GAS_5_BUTTON_POSITION.y);
	fill_10_Sprite_ = new Sprite (GAS_10_BUTTON_INFO.idlePath, GAS_10_BUTTON_INFO.width, GAS_10_BUTTON_INFO.height, GAS_10_BUTTON_POSITION.x, GAS_10_BUTTON_POSITION.y);
	fill_25_Sprite_ = new Sprite (GAS_25_BUTTON_INFO.idlePath, GAS_25_BUTTON_INFO.width, GAS_25_BUTTON_INFO.height, GAS_25_BUTTON_POSITION.x, GAS_25_BUTTON_POSITION.y);
	backSprite_ = new Sprite (BACK_BUTTON_INFO.idlePath, BACK_BUTTON_INFO.width, BACK_BUTTON_INFO.height, BACK_BUTTON_POSITION.x, BACK_BUTTON_POSITION.y);

	buttons_["fill_5_Button"]->addRenderComponent (fill_5_Sprite_);
	buttons_["fill_10_Button"]->addRenderComponent (fill_10_Sprite_);
	buttons_["fill_25_Button"]->addRenderComponent (fill_25_Sprite_);
	buttons_["backButton"]->addRenderComponent (backSprite_);
}
