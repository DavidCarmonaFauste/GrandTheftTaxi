#include "MoneyDisplay.h"
#include "Events.h"
#include "Game.h"


MoneyDisplay::MoneyDisplay(Font* font, SDL_Color fontColor, int currentMoney) {
	textSprite_ = new Text(font, "0", fontColor);
	textSprite_->setCamera(UI_CAMERA);
	setMoney(currentMoney);

	addRenderComponent(textSprite_);
}


MoneyDisplay::~MoneyDisplay() {

}

void MoneyDisplay::setMoney(int money) {
	textSprite_->setText(to_string(money) + currencyString_);
	Vector2D pos;		
	pos.x = (textSprite_->getCamera()->getWidth() - (1 * textSprite_->getText().length()) - textSprite_->getFont()->getSize() / 2);
	pos.y = (textSprite_->getFont()->getSize()*0.5);
	reposition(pos,1);
}

void MoneyDisplay::setSimpleMoney(int money)
{
	textSprite_->setText(to_string(money) + currencyString_);
}


void MoneyDisplay::reposition(Vector2D v, double increase) {
	// Recalculate width and height
	setWidth((textSprite_->getFont()->getSize() / 2 * textSprite_->getText().length())*increase);
	setHeight((textSprite_->getFont()->getSize())*increase);

	v.x -= width_;

	setPosition(v);
}