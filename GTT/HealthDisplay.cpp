#include "HealthDisplay.h"


HealthDisplay::HealthDisplay() {
	setPosition(Vector2D(35, 35));
	setWidth(200); setHeight(50);

	background = new Sprite("./../Assets/sprites/health_background.png");
	background->setCamera(UI_CAMERA);

	bar = new Sprite("./../Assets/sprites/health_bar.png");
	bar->setCamera(UI_CAMERA);
	bar->setAutoSize(false);
	bar->setSize(getWidth(), getHeight());

	addRenderComponent(background);
	addRenderComponent(bar);

	bar_clip = new SDL_Rect();
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
}

int HealthDisplay::getHealthPercentage() {
	return healthPercentage_;
}
