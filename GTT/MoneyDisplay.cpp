#include "MoneyDisplay.h"
#include "Resources.h"
#include "Events.h"


MoneyDisplay::MoneyDisplay(Font* font, SDL_Color fontColor) {
	setPosition(Vector2D(900, 100));

	textSprite_ = new Text(font, "0", fontColor);
	setWidth(font->getSize() / 2 * textSprite_->getText().length());
	setHeight(font->getSize());

	addRenderComponent(textSprite_);
}


MoneyDisplay::~MoneyDisplay() {

}

void MoneyDisplay::setMoney(int money) {
	textSprite_->setText(to_string(money));
	setWidth(textSprite_->getFont()->getSize() / 2 * textSprite_->getText().length());
}
