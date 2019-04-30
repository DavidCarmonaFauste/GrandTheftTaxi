#include "GasMainMenu.h"
#include "Reticule.h"
#include "Game.h"
#include "Vehicle.h"

GasMainMenu::GasMainMenu () {
}


GasMainMenu::~GasMainMenu () {
	while (!stage_.empty()) {
		delete stage_.back();
		stage_.back() = nullptr;
		stage_.pop_back();
	}
	delete backgroundSprite_;
	delete fillSprite_;
	delete gunSprite_;
	delete backSprite_;
}

void GasMainMenu::start () {
	taxiPos_ = Vehicle::getInstance ()->getPosition ();
	
	int i; //recoge el valor del index si el elemento está en el vector
	if (!isRegistered(this, i))
		registerObserver(this);

	int j; //recoge el valor del index si el elemento está en el vector
	if (!isRegistered(Vehicle::getInstance(), j))
		registerObserver (Vehicle::getInstance());

	Game::getInstance()->getCamera(GAME_CAMERA)->setZoom(1.0, false);
	Game::getInstance()->getCamera(UI_CAMERA)->setZoom(1.0, false);
	
	// BACKGROUND
	setBackground ();

	// BUTTONS
	setButtons ();
	setButtonComponents ();

	
	//Container to GameObj list
	stage_.push_back(background_);
	stage_.push_back(buttons_["fillGasButton"]);
	stage_.push_back(buttons_["gunShopButton"]);
	stage_.push_back(buttons_["backButton"]);
	stage_.push_back(Reticule::getInstance());
}

void GasMainMenu::end () {
}

void GasMainMenu::update (Uint32 deltaTime) {
	Game::getInstance()->getCamera(GAME_CAMERA)->setCentered(false);
	Game::getInstance()->getCamera(UI_CAMERA)->setCentered(false);

	GameState::update(deltaTime);
}

bool GasMainMenu::receiveEvent (Event & e) {
	switch (e.type_)
	{
	case CLICK_BUTTON: {
		MouseClickLeft  MouseClickLeft_ = static_cast<MouseClickLeft&>(e);

		if (MouseClickLeft_.button_ == buttons_["fillGasButton"]->getIndex()) {
			cout << "fill gas\n";
		}
		else if (MouseClickLeft_.button_ == buttons_["gunShopButton"]->getIndex ()) {
			cout << "nothing here yet\n";
		}
		else if (MouseClickLeft_.button_ == buttons_["backButton"]->getIndex ()) {
			LoadTaxiPositionEvent e (this, taxiPos_);
			Game::getInstance ()->setState (NAME_MAIN_STATE);
			broadcastEvent (e);
		}
		break;
	}
	default:
		break;
	}
	return true;
}

void GasMainMenu::setBackground () {
	backgroundSprite_ = new Sprite (GAS_BACKGROUND_INFO.idlePath, GAS_BACKGROUND_INFO.width, GAS_BACKGROUND_INFO.height);
	
	background_ = new Container ();

	background_->setWidth (GAS_BACKGROUND_W);
	background_->setHeight (GAS_BACKGROUND_H);
	background_->addRenderComponent (backgroundSprite_);
}

void GasMainMenu::setButtons () {
	// build
	buttons_["fillGasButton"] = new Button();
	buttons_["fillGasButton"]->getMouseClickIC()->registerObserver(this);
	buttons_["gunShopButton"] = new Button();
	buttons_["gunShopButton"]->getMouseClickIC()->registerObserver(this);
	buttons_["backButton"] = new Button();
	buttons_["backButton"]->getMouseClickIC()->registerObserver(this);

	// set
	buttons_["fillGasButton"]->setPosition(FILL_GAS_BUTTON_POSITION);
	buttons_["fillGasButton"]->setWidth(FILL_GAS_BUTTON_INFO.width);
	buttons_["fillGasButton"]->setHeight(FILL_GAS_BUTTON_INFO.height);
	buttons_["fillGasButton"]->setIndex(1);

	buttons_["gunShopButton"]->setPosition(GUN_SHOP_BUTTON_POSITION);
	buttons_["gunShopButton"]->setWidth(GUN_SHOP_BUTTON_INFO.width);
	buttons_["gunShopButton"]->setHeight(GUN_SHOP_BUTTON_INFO.height);
	buttons_["gunShopButton"]->setIndex(2);

	buttons_["backButton"]->setPosition(BACK_BUTTON_POSITION);
	buttons_["backButton"]->setWidth(BACK_BUTTON_INFO.width);
	buttons_["backButton"]->setHeight(BACK_BUTTON_INFO.height);
	buttons_["backButton"]->setIndex(3);
}

void GasMainMenu::setButtonComponents () {
	fillSprite_ = new Sprite (FILL_GAS_BUTTON_INFO.idlePath, FILL_GAS_BUTTON_INFO.width, FILL_GAS_BUTTON_INFO.height, FILL_GAS_BUTTON_POSITION.x, FILL_GAS_BUTTON_POSITION.y);
	gunSprite_ = new Sprite (GUN_SHOP_BUTTON_INFO.idlePath, GUN_SHOP_BUTTON_INFO.width, GUN_SHOP_BUTTON_INFO.height, GUN_SHOP_BUTTON_POSITION.x, GUN_SHOP_BUTTON_POSITION.y);
	backSprite_ = new Sprite (BACK_BUTTON_INFO.idlePath, BACK_BUTTON_INFO.width, BACK_BUTTON_INFO.height, BACK_BUTTON_POSITION.x, BACK_BUTTON_POSITION.y);

	buttons_["fillGasButton"]->addRenderComponent (fillSprite_);
	buttons_["gunShopButton"]->addRenderComponent (gunSprite_);
	buttons_["backButton"]->addRenderComponent (backSprite_);
}
