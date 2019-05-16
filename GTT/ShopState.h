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

	map<string, Button*> buttons_;

	Container *background_, *bckPistol_, *bckShotgun_, *bckRifle_, *bckMachinegun_;
	Sprite *backgroundSprite_, *bckPistolSprite_, *bckShotgunSprite_, *bckRifleSprite_, *bckMachinegunSprite_;

	Sprite *backSprite_;

	Container *armory_, *inventory_;
	Text *armoryText_, *inventoryText_;

	void setButtons();
	void setBackground();
	void setButtonComponents();

	void startTexts();
};

