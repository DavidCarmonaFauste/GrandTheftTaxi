
#include "UI.h"

UI::UI(Vehicle* v) {
	UIElements_ = vector<GameObject*>();

	// Common font for all UI elements
	font_ = new Font(FONT_LATO, 60);
	fontColor_ = SDL_Color();
	fontColor_.r = 255; fontColor_.g = 255; fontColor_.b = 255;

	// DISPLAYS

	// Health
	healthDisplay_ = new HealthDisplay();
	UIElements_.push_back(healthDisplay_);

	// Money
	moneyDisplay_ = new MoneyDisplay(font_, fontColor_);
	UIElements_.push_back(moneyDisplay_);

	//Ammo
	ammoDisplay_ = new AmmoDisplay(v);
	UIElements_.push_back(ammoDisplay_);

	//Reload
	reloadDisplay_ = new ReloadingDisplay(v);
	UIElements_.push_back(reloadDisplay_);

}


UI::~UI() {
	for (auto e : UIElements_) {
		delete e; e = nullptr;
	}
	UIElements_.clear();
}

void UI::render(Uint32 deltaTime) {
	for (auto element : UIElements_) {
		element->render(deltaTime);
	}
}

void UI::update(Uint32 deltaTime)
{
	if (reloadDisplay_ != nullptr)
		reloadDisplay_->setActive(reloadDisplay_->isReloading());
	for (auto element : UIElements_) {
		element->update(deltaTime);
	}
}

void UI::addUIElement(Container * c)
{
	UIElements_.push_back(c);
}


bool UI::receiveEvent(Event& e) {
	if (e.type_ == HEALTH_CHANGED) {
		HealthChangedEvent* he = static_cast<HealthChangedEvent*>(&e);
		healthDisplay_->setHealthPercentage((float) he->currentHealth_/he->maxHealth_);
	}
	else if (e.type_ == MONEY_CHANGED) {
		moneyDisplay_->setMoney(static_cast<MoneyChangedEvent*>(&e)->currentMoney_);
	}

	return true;
}

