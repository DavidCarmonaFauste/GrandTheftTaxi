#include "ShopState.h"
#include "Reticule.h"
#include "Game.h"

ShopState::ShopState() {
}

ShopState::~ShopState() {
	delete backSprite_;
	delete backgroundSprite_;
	delete bckPistolSprite_;
	delete bckShotgunSprite_;
	delete bckRifleSprite_;
	delete bckMachinegunSprite_;

	for (auto button : buttons_) {
		delete button.second; button.second = nullptr;
	}
	buttons_.clear();
}

void ShopState::start() {
	int i; //recoge el valor del index si el elemento está en el vector
	if (!isRegistered(this, i))
		registerObserver(this);

	Game::getInstance()->getCamera(GAME_CAMERA)->setZoom(1.0, false);
	Game::getInstance()->getCamera(UI_CAMERA)->setZoom(1.0, false);

	setBackground();
	setButtons();
	setButtonComponents();
	startTexts();

	//Container to GameObj list
	stage_.push_back(background_);				//Backgrounds
	stage_.push_back(bckPistol_);
	stage_.push_back(bckShotgun_);
	stage_.push_back(bckRifle_);
	stage_.push_back(bckMachinegun_);

	stage_.push_back(buttons_["backButton"]);	//Buttons

	stage_.push_back(armory_);			//Texts
	stage_.push_back(inventory_);

	stage_.push_back(Reticule::getInstance());
}

void ShopState::end() {
}

void ShopState::update(Uint32 deltaTime) {
	Game::getInstance()->getCamera(GAME_CAMERA)->setCentered(false);
	Game::getInstance()->getCamera(UI_CAMERA)->setCentered(false);

	GameState::update(deltaTime);
}

bool ShopState::receiveEvent(Event & e)
{
	switch (e.type_)
	{
	case CLICK_BUTTON: {
		MouseClickLeft  MouseClickLeft_ = static_cast<MouseClickLeft&>(e);
		if (MouseClickLeft_.button_ == buttons_["backButton"]->getIndex())
			Game::getInstance()->getGameStateMachine()->fromFillMenuToGasMainMenu();
	}
	default:
		break;
	}
	return true;
}

void ShopState::setButtons()
{
	//Build
	buttons_["backButton"] = new Button();
	buttons_["backButton"]->getMouseClickIC()->registerObserver(this);

	//Set
	buttons_["backButton"]->setPosition(BACK_BUTTON_POSITION);
	buttons_["backButton"]->setWidth(BACK_BUTTON_INFO.width);
	buttons_["backButton"]->setHeight(BACK_BUTTON_INFO.height);
	buttons_["backButton"]->setIndex(1);
}

void ShopState::setBackground()
{
	//Global background
	backgroundSprite_ = new Sprite(GAS_BACKGROUND_INFO.idlePath, GAS_BACKGROUND_INFO.width, GAS_BACKGROUND_INFO.height);
	background_ = new Container();

	background_->setWidth(GAS_BACKGROUND_W);
	background_->setHeight(GAS_BACKGROUND_H);
	background_->addRenderComponent(backgroundSprite_);

	//Weapons backgrounds
	bckPistolSprite_ = new Sprite(BLACK_BACKGROUND_INFO.idlePath, WEAPONS_BACKGROUNDS_W, WEAPONS_BACKGROUNDS_H);
	bckPistol_ = new Container();

	bckPistol_->setWidth(WEAPONS_BACKGROUNDS_W);
	bckPistol_->setHeight(WEAPONS_BACKGROUNDS_H);
	bckPistol_->addRenderComponent(bckPistolSprite_);

	bckShotgunSprite_ = new Sprite(BLACK_BACKGROUND_INFO.idlePath, WEAPONS_BACKGROUNDS_W, WEAPONS_BACKGROUNDS_H);
	bckShotgun_ = new Container();

	bckShotgun_->setWidth(WEAPONS_BACKGROUNDS_W);
	bckShotgun_->setHeight(WEAPONS_BACKGROUNDS_H);
	bckShotgun_->addRenderComponent(bckShotgunSprite_);

	bckRifleSprite_ = new Sprite(BLACK_BACKGROUND_INFO.idlePath, WEAPONS_BACKGROUNDS_W, WEAPONS_BACKGROUNDS_H);
	bckRifle_ = new Container();

	bckRifle_->setWidth(WEAPONS_BACKGROUNDS_W);
	bckRifle_->setHeight(WEAPONS_BACKGROUNDS_H);
	bckRifle_->addRenderComponent(bckRifleSprite_);

	bckMachinegunSprite_ = new Sprite(BLACK_BACKGROUND_INFO.idlePath, WEAPONS_BACKGROUNDS_W, WEAPONS_BACKGROUNDS_H);
	bckMachinegun_ = new Container();

	bckMachinegun_->setWidth(WEAPONS_BACKGROUNDS_W);
	bckMachinegun_->setHeight(WEAPONS_BACKGROUNDS_H);
	bckMachinegun_->addRenderComponent(bckMachinegunSprite_);
}

void ShopState::setButtonComponents()
{
	//Create Sprite
	backSprite_ = new Sprite(BACK_BUTTON_INFO.idlePath, BACK_BUTTON_INFO.width, BACK_BUTTON_INFO.height, BACK_BUTTON_POSITION.x, BACK_BUTTON_POSITION.y);

	//Add rendercomponent
	buttons_["backButton"]->addRenderComponent(backSprite_);
}

void ShopState::startTexts()
{
	//Armory
	armory_ = new Container();
	armoryText_ = new Text(new Font(FONT_COOLFONT, 50), "Armory", SDL_Color({ 255, 255, 255 }));
	armoryText_->setCamera(UI_CAMERA);
	armory_->setWidth(armoryText_->getFont()->getSize()*armoryText_->getText().length());
	armory_->setHeight(armoryText_->getFont()->getSize());
	armory_->setPosition(ARMORY_TEXT_POSITION);
	armory_->addRenderComponent(armoryText_);

	//Inventory
	inventory_ = new Container();
	inventoryText_ = new Text(new Font(FONT_COOLFONT, 50), "Inventory", SDL_Color({ 255, 255, 255 }));
	inventoryText_->setCamera(UI_CAMERA);
	inventory_->setWidth(inventoryText_->getFont()->getSize()*inventoryText_->getText().length());
	inventory_->setHeight(inventoryText_->getFont()->getSize());
	inventory_->setPosition(ARMORY_TEXT_POSITION);
	inventory_->addRenderComponent(inventoryText_);
}

