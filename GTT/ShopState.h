#pragma once
#include "GameState.h"
#include "Button.h"
#include "Observer.h"
#include "HealthDisplay.h"
#include "MoneyDisplay.h"


class ShopState : public GameState, public Observer, public Observable {
public:
	ShopState();
	virtual ~ShopState();

	virtual void start() override;
	virtual void end() override;

	virtual void update(Uint32 deltaTime) override;
	virtual bool receiveEvent(Event& e);

private:
		//Buttons
	map<string, Button*> buttons_;
	Sprite *weapon1ButtonSprite_, *weapon2ButtonSprite_, *weapon3ButtonSprite_, *weapon4ButtonSprite_;

		//Backgrounds
	Container *background_, *bckPistol_, *bckShotgun_, *bckRifle_, *bckMachinegun_, *weapon1_, *weapon2_;
	Sprite *backSprite_, *backgroundSprite_, *bckPistolSprite_, *bckShotgunSprite_, *bckRifleSprite_, *bckMachinegunSprite_, *weapon1Sprite_, *weapon2Sprite_;
	
		//Texts
	Container *armory_, *inventory_, *pistolT_, *shotgunT_, *rifleT_, *machinegunT_;
	Text *armoryText_, *inventoryText_, *shotgunText_, *pistolText_, *rifleText_, *machinegunText_;

		//Icons
	Container *pistol_, *shotgun_, *rifle_, *machinegun_;
	Sprite *pistolSprite_, *shotgunSprite_, *rifleSprite_, *machinegunSprite_;

	void setButtons();
	void setBackground();
	void setButtonComponents();
	void startTexts();
	void startIcons();
};

