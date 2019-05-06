#pragma once
#include "Container.h"
#include "Observer.h"
#include "Text.h"

class MoneyDisplay : public Container {
public:
	MoneyDisplay(Font* font = new Font(FONT_LATO, 60), SDL_Color fontColor = SDL_Color({255, 255, 255}), int currentMoney = 0);
	virtual ~MoneyDisplay();

	void setMoney(int money);
	void reposition();

private:
	Text* textSprite_;
	string currencyString_ = " $";
};

