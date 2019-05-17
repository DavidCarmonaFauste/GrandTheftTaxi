#include "ShopState.h"
#include "Reticule.h"
#include "Game.h"
#include <string.h>

ShopState::ShopState() {
}

ShopState::~ShopState() {
	delete backSprite_;
	delete backgroundSprite_;
	delete bckPistolSprite_;
	delete bckShotgunSprite_;
	delete bckRifleSprite_;
	delete bckMachinegunSprite_;
	delete weapon1ButtonSprite_;
	delete weapon2ButtonSprite_;
	delete weapon3ButtonSprite_;
	delete weapon4ButtonSprite_;
	delete pistolSprite_;
	delete shotgunSprite_;
	delete rifleSprite_;
	delete machinegunSprite_;
	delete weapon1Sprite_;
	delete weapon2Sprite_;

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
	startIcons();

	//Container to GameObj list
	stage_.push_back(background_);				//Backgrounds
	stage_.push_back(bckPistol_);
	stage_.push_back(bckShotgun_);
	stage_.push_back(bckRifle_);
	stage_.push_back(bckMachinegun_);
	stage_.push_back(weapon1_);
	stage_.push_back(weapon2_);


	stage_.push_back(buttons_["backButton"]);		//Buttons
	stage_.push_back(buttons_["weapon1Button"]);
	stage_.push_back(buttons_["weapon2Button"]);
	stage_.push_back(buttons_["weapon3Button"]);
	stage_.push_back(buttons_["weapon4Button"]);

	stage_.push_back(pistol_);						//Icons
	stage_.push_back(shotgun_);
	stage_.push_back(rifle_);
	stage_.push_back(machinegun_);


	stage_.push_back(armory_);			//Texts
	stage_.push_back(inventory_);
	stage_.push_back(pistolT_);
	stage_.push_back(shotgunT_);
	stage_.push_back(rifleT_);
	stage_.push_back(machinegunT_);



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
	buttons_["weapon1Button"] = new Button();
	buttons_["weapon1Button"]->getMouseClickIC()->registerObserver(this);
	buttons_["weapon2Button"] = new Button();
	buttons_["weapon2Button"]->getMouseClickIC()->registerObserver(this);
	buttons_["weapon3Button"] = new Button();
	buttons_["weapon3Button"]->getMouseClickIC()->registerObserver(this);
	buttons_["weapon4Button"] = new Button();
	buttons_["weapon4Button"]->getMouseClickIC()->registerObserver(this);

	//Set
	buttons_["backButton"]->setPosition(BACK_BUTTON_POSITION);
	buttons_["backButton"]->setWidth(BACK_BUTTON_INFO.width);
	buttons_["backButton"]->setHeight(BACK_BUTTON_INFO.height);
	buttons_["backButton"]->setIndex(1);

	buttons_["weapon1Button"]->setPosition(Vector2D(FIRST_WEAPON_BCK.x + WEAPONS_BACKGROUNDS_W + WEAPON_BUTTON_W ,FIRST_WEAPON_BCK.y));
	buttons_["weapon1Button"]->setWidth(WEAPON_BUTTON_W);
	buttons_["weapon1Button"]->setHeight(WEAPON_BUTTON_H);
	buttons_["weapon1Button"]->setIndex(2);

	buttons_["weapon2Button"]->setPosition(Vector2D(FIRST_WEAPON_BCK.x + WEAPONS_BACKGROUNDS_W + WEAPON_BUTTON_W , FIRST_WEAPON_BCK.y + 125));
	buttons_["weapon2Button"]->setWidth(WEAPON_BUTTON_W);
	buttons_["weapon2Button"]->setHeight(WEAPON_BUTTON_H);
	buttons_["weapon2Button"]->setIndex(3);

	buttons_["weapon3Button"]->setPosition(Vector2D(FIRST_WEAPON_BCK.x + WEAPONS_BACKGROUNDS_W + WEAPON_BUTTON_W , FIRST_WEAPON_BCK.y + 250));
	buttons_["weapon3Button"]->setWidth(WEAPON_BUTTON_W);
	buttons_["weapon3Button"]->setHeight(WEAPON_BUTTON_H);
	buttons_["weapon3Button"]->setIndex(4);

	buttons_["weapon4Button"]->setPosition(Vector2D(FIRST_WEAPON_BCK.x + WEAPONS_BACKGROUNDS_W + WEAPON_BUTTON_W , FIRST_WEAPON_BCK.y + 375));
	buttons_["weapon4Button"]->setWidth(WEAPON_BUTTON_W);
	buttons_["weapon4Button"]->setHeight(WEAPON_BUTTON_H);
	buttons_["weapon4Button"]->setIndex(5);
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
	bckPistol_->setPosition(FIRST_WEAPON_BCK);

	bckShotgunSprite_ = new Sprite(BLACK_BACKGROUND_INFO.idlePath, WEAPONS_BACKGROUNDS_W, WEAPONS_BACKGROUNDS_H);
	bckShotgun_ = new Container();

	bckShotgun_->setWidth(WEAPONS_BACKGROUNDS_W);
	bckShotgun_->setHeight(WEAPONS_BACKGROUNDS_H);
	bckShotgun_->addRenderComponent(bckShotgunSprite_);
	bckShotgun_->setPosition(Vector2D(FIRST_WEAPON_BCK.x, FIRST_WEAPON_BCK.y + 125));

	bckRifleSprite_ = new Sprite(BLACK_BACKGROUND_INFO.idlePath, WEAPONS_BACKGROUNDS_W, WEAPONS_BACKGROUNDS_H);
	bckRifle_ = new Container();

	bckRifle_->setWidth(WEAPONS_BACKGROUNDS_W);
	bckRifle_->setHeight(WEAPONS_BACKGROUNDS_H);
	bckRifle_->addRenderComponent(bckRifleSprite_);
	bckRifle_->setPosition(Vector2D(FIRST_WEAPON_BCK.x, FIRST_WEAPON_BCK.y + 250));

	bckMachinegunSprite_ = new Sprite(BLACK_BACKGROUND_INFO.idlePath, WEAPONS_BACKGROUNDS_W, WEAPONS_BACKGROUNDS_H);
	bckMachinegun_ = new Container();

	bckMachinegun_->setWidth(WEAPONS_BACKGROUNDS_W);
	bckMachinegun_->setHeight(WEAPONS_BACKGROUNDS_H);
	bckMachinegun_->addRenderComponent(bckMachinegunSprite_);
	bckMachinegun_->setPosition(Vector2D(FIRST_WEAPON_BCK.x, FIRST_WEAPON_BCK.y + 375));

	//Inventory backgrounds
	weapon1Sprite_ = new Sprite(BLACK_BACKGROUND_INFO.idlePath, INV_W, INV_H);
	weapon1_ = new Container();

	weapon1_->setWidth(INV_W);
	weapon1_->setHeight(INV_H);
	weapon1_->addRenderComponent(weapon1Sprite_);
	weapon1_->setPosition(INV1_POSITION);
	
	weapon2Sprite_ = new Sprite(BLACK_BACKGROUND_INFO.idlePath, INV_W, INV_H);
	weapon2_ = new Container();

	weapon2_->setWidth(INV_W);
	weapon2_->setHeight(INV_H);
	weapon2_->addRenderComponent(weapon2Sprite_);
	weapon2_->setPosition(INV2_POSITION);

}

void ShopState::setButtonComponents()
{
	//Create Sprite
	backSprite_ = new Sprite(BACK_BUTTON_INFO.idlePath, BACK_BUTTON_INFO.width, BACK_BUTTON_INFO.height, BACK_BUTTON_POSITION.x, BACK_BUTTON_POSITION.y);
	weapon1ButtonSprite_ = new Sprite(BACK_BUTTON_INFO.idlePath, WEAPON_BUTTON_W, WEAPON_BUTTON_H, 0, 0);
	weapon2ButtonSprite_ = new Sprite(BACK_BUTTON_INFO.idlePath, WEAPON_BUTTON_W, WEAPON_BUTTON_H, 0, 0);
	weapon3ButtonSprite_ = new Sprite(BACK_BUTTON_INFO.idlePath, WEAPON_BUTTON_W, WEAPON_BUTTON_H, 0, 0);
	weapon4ButtonSprite_ = new Sprite(BACK_BUTTON_INFO.idlePath, WEAPON_BUTTON_W, WEAPON_BUTTON_H, 0, 0);

	//Add rendercomponent
	buttons_["backButton"]->addRenderComponent(backSprite_);
	buttons_["weapon1Button"]->addRenderComponent(weapon1ButtonSprite_);
	buttons_["weapon2Button"]->addRenderComponent(weapon2ButtonSprite_);
	buttons_["weapon3Button"]->addRenderComponent(weapon3ButtonSprite_);
	buttons_["weapon4Button"]->addRenderComponent(weapon4ButtonSprite_);

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
	inventory_->setPosition(INVENTORY_TEXT_POSITION);
	inventory_->addRenderComponent(inventoryText_);

	//Weapon names
	pistolT_ = new Container();
	pistolText_ = new Text(new Font(FONT_LATO, 30), "Pistol - FREE" , SDL_Color({ 255, 255, 255 }));
	pistolText_->setCamera(UI_CAMERA);
	pistolT_->setWidth(pistolText_->getFont()->getSize()*pistolText_->getText().length() / 2);
	pistolT_->setHeight(pistolText_->getFont()->getSize());
	pistolT_->setPosition(Vector2D(FIRST_WEAPON_BCK.x + WEAPONS_BACKGROUNDS_W / 2, FIRST_WEAPON_BCK.y + WEAPONS_BACKGROUNDS_H / 2 - pistolText_->getFont()->getSize()/2 ));
	pistolT_->addRenderComponent(pistolText_);

	shotgunT_ = new Container();
	shotgunText_ = new Text(new Font(FONT_LATO, 30), "Shotgun - " + SHOTGUN_PRICE, SDL_Color({ 255, 255, 255 }));
	shotgunText_->setCamera(UI_CAMERA);
	shotgunT_->setWidth(shotgunText_->getFont()->getSize()*shotgunText_->getText().length() / 2);
	shotgunT_->setHeight(shotgunText_->getFont()->getSize());
	shotgunT_->setPosition(Vector2D(FIRST_WEAPON_BCK.x + WEAPONS_BACKGROUNDS_W / 2, 125 + FIRST_WEAPON_BCK.y + WEAPONS_BACKGROUNDS_H / 2 - shotgunText_->getFont()->getSize() / 2));
	shotgunT_->addRenderComponent(shotgunText_);

	rifleT_ = new Container();
	rifleText_ = new Text(new Font(FONT_LATO, 30), "Sniper - " + RIFLE_PRICE, SDL_Color({ 255, 255, 255 }));
	rifleText_->setCamera(UI_CAMERA);
	rifleT_->setWidth(rifleText_->getFont()->getSize()*rifleText_->getText().length() / 2);
	rifleT_->setHeight(rifleText_->getFont()->getSize());
	rifleT_->setPosition(Vector2D(FIRST_WEAPON_BCK.x + WEAPONS_BACKGROUNDS_W / 2, 250 + FIRST_WEAPON_BCK.y + WEAPONS_BACKGROUNDS_H / 2 - rifleText_->getFont()->getSize() / 2));
	rifleT_->addRenderComponent(rifleText_);

	machinegunT_ = new Container();
	machinegunText_ = new Text(new Font(FONT_LATO, 30), "Machinegun - " + MACHINEGUN_PRICE, SDL_Color({ 255, 255, 255 }));
	machinegunText_->setCamera(UI_CAMERA);
	machinegunT_->setWidth(machinegunText_->getFont()->getSize()*machinegunText_->getText().length() / 1.8);
	machinegunT_->setHeight(machinegunText_->getFont()->getSize());
	machinegunT_->setPosition(Vector2D(FIRST_WEAPON_BCK.x + WEAPONS_BACKGROUNDS_W / 2 - 35, 375 + FIRST_WEAPON_BCK.y + WEAPONS_BACKGROUNDS_H / 2 - machinegunText_->getFont()->getSize() / 2));
	machinegunT_->addRenderComponent(machinegunText_);
}

void ShopState::startIcons()
{
	pistolSprite_ = new Sprite(GUN.idlePath, ICON_W, ICON_H);
	pistol_ = new Container();

	pistol_->setWidth(ICON_W);
	pistol_->setHeight(ICON_H * 1.65);
	pistol_->addRenderComponent(pistolSprite_);
	pistol_->setPosition(Vector2D(FIRST_WEAPON_BCK.x + WEAPONS_BACKGROUNDS_W * 0.10, FIRST_WEAPON_BCK.y - (ICON_H / 3.5)));
	pistol_->setRotation(90);

	shotgunSprite_ = new Sprite(SHOTGUN.idlePath, ICON_W, ICON_H);
	shotgun_ = new Container();

	shotgun_->setWidth(ICON_W * 0.8);
	shotgun_->setHeight(ICON_H * 2.6 * 0.8);
	shotgun_->addRenderComponent(shotgunSprite_);
	shotgun_->setPosition(Vector2D(FIRST_WEAPON_BCK.x + WEAPONS_BACKGROUNDS_W * 0.10, FIRST_WEAPON_BCK.y + 125 - shotgun_->getHeight() / 3.6));
	shotgun_->setRotation(90);

	rifleSprite_ = new Sprite(SNIPER.idlePath, ICON_W, ICON_H);
	rifle_ = new Container();

	rifle_->setWidth(ICON_W * 0.4);
	rifle_->setHeight(ICON_H * 6 * 0.4);
	rifle_->addRenderComponent(rifleSprite_);
	rifle_->setPosition(Vector2D(FIRST_WEAPON_BCK.x + WEAPONS_BACKGROUNDS_W * 0.15, FIRST_WEAPON_BCK.y + 250 - rifle_->getHeight() / 3.5));
	rifle_->setRotation(90);

	machinegunSprite_ = new Sprite(MACHINEGUN.idlePath, ICON_W, ICON_H);
	machinegun_ = new Container();

	machinegun_->setWidth(ICON_W);
	machinegun_->setHeight(ICON_H * 1.8);
	machinegun_->addRenderComponent(machinegunSprite_);
	machinegun_->setPosition(Vector2D(FIRST_WEAPON_BCK.x + WEAPONS_BACKGROUNDS_W * 0.10, FIRST_WEAPON_BCK.y + 375 - machinegun_->getHeight() / 3.7));
	machinegun_->setRotation(90);

}

