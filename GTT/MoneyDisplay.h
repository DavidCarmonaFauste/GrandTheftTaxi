#pragma once
#include "Container.h"
#include "Observer.h"
#include "Text.h"

class MoneyDisplay : public Container {
public:
	MoneyDisplay(Font* font, SDL_Color fontColor, int currentMoney = 0);
	virtual ~MoneyDisplay();

	void setMoney(int money);
	void reposition();

private:
	Text* textSprite_;
	string currencyString_ = " $";
};

