#include "HealthDisplay.h"
#include <string>

HealthDisplay::HealthDisplay() {
	setPosition(Vector2D(35, 35));
	setWidth(200); setHeight(50);
	
	//fuHealth  display background
	background = new Sprite("./../Assets/sprites/health_background.png");
	background->setCamera(UI_CAMERA);

	//fuHealth  display foreground
	bar = new Sprite("./../Assets/sprites/health_bar.png");
	bar->setCamera(UI_CAMERA);
	bar->setAutoSize(false);
	bar->setSize(getWidth(), getHeight());

	addRenderComponent(background);
	addRenderComponent(bar);

	bar_clip = new SDL_Rect();

	//Percentage of current fuHealth
	SDL_Color fontColor = SDL_Color();
	fontColor.r = 255; fontColor.g = 255; fontColor.b = 255;
	Font* f = new Font(FONT_LATO, 60);
	fuhealthAmount_ = new Text(f, "", fontColor);
	fuhealthAmount_->setCamera(UI_CAMERA);
	addRenderComponent(fuhealthAmount_);
	fuhealthAmount_->setText(to_string((int)(healthPercentage_ * 100)) + " %");
	fuhealthAmount_->setAutoPos(false);
	fuhealthAmount_->setPos(getPosition().x + 200, getPosition().y + 4);
	fuhealthAmount_->setAutoSize(false);
	fuhealthAmount_->setSize(90, 40);
}

HealthDisplay::~HealthDisplay() {

}

// Percentage from 0 to 1
void HealthDisplay::setHealthPercentage(float healthPercentage) {
	healthPercentage_ = healthPercentage;

	Texture* tex = bar->getTexture();
	bar_clip->x = bar_clip->y = 0;
	bar_clip->w = tex->getWidth() * healthPercentage_;
	bar_clip->h = tex->getHeight();

	bar->setSize(getWidth() * healthPercentage_, getHeight());
	bar->setClipRect(bar_clip);
	
	fuhealthAmount_->setText(to_string((int)(healthPercentage_ * 100)) + " %");
}

int HealthDisplay::getHealthPercentage() {
	return healthPercentage_;
}
