#include "MoneyDisplay.h"
#include "Events.h"


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
	reposition(); 
}

void MoneyDisplay::reposition() {
	// Recalculate width and height
	setWidth(textSprite_->getFont()->getSize() / 2 * textSprite_->getText().length());
	setHeight(textSprite_->getFont()->getSize());

	// Reposition
	Vector2D pos;
	pos.x = (textSprite_->getCamera()->getWidth() - width_ - textSprite_->getFont()->getSize()/2);
	pos.y = (textSprite_->getFont()->getSize()*0.5);
	setPosition(pos);
}