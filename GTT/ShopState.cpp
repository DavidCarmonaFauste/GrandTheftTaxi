#include "ShopState.h"
#include "Health.h"
#include "Reticule.h"


ShopState::ShopState() {
	// UI
	//UI::getInstance()->setAmmoActive(false);
	stage_.push_back(UI::getInstance());

	//refillButton_ = new Button(refillCallback);
	//stage_.push_back(refillButton_);

	Money::getInstance()->setCurrentMoney(100);

	stage_.push_back(Reticule::getInstance());
}

ShopState::~ShopState() {

}

void ShopState::start() {
	UI::getInstance()->setAmmoActive(false);
}

void ShopState::end() {
	UI::getInstance()->setAmmoActive(true);
}

void ShopState::update(Uint32 deltaTime) {
	GameState::update(deltaTime);

	//if (refillButton_->isMouseClickICEvent()) refillButton_->callback();
}

void ShopState::handleEvents(Uint32 deltaTime, SDL_Event & event) {
	GameState::handleEvents(deltaTime, event);

	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == DEFAULT_KEYS.mainMenu) {
			Game::getInstance()->setState(NAME_MAIN_STATE);
		}
	}
}

void ShopState::refillCallback() {
	Health *h = Vehicle::getInstance()->getHealthComponent();
	Money *m = Money::getInstance();

	// Exit if HP is at max or there is no money
	if (h->getHealth() >= h->getMaxHealth() || m->getCurrentMoney() <= 0)
		return;

	int money = m->getCurrentMoney();
//	int cost = FUEL_VALUE * (h->getMaxHealth() - h->getHealth());
	/*
	if (money >= cost) {
		m->setCurrentMoney(m->getCurrentMoney() - cost);
		h->resetHealth();
	}
	else {
		m->setCurrentMoney(0);
		h->heal(money/FUEL_VALUE);
		
	}
	*/
}

