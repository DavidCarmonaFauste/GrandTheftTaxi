#pragma once
#include "Container.h"
#include "Observer.h"
#include "Text.h"

class MoneyDisplay : public Container {
public:
	MoneyDisplay(Font* font, SDL_Color fontColor);
	virtual ~MoneyDisplay();

	void setMoney(int money);

private:
	Text* textSprite_;
};

