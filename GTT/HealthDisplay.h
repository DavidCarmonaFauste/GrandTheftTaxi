#pragma once
#include "Container.h"
#include "Sprite.h"
#include "Text.h"

class HealthDisplay : public Container {
public:
	HealthDisplay();
	virtual ~HealthDisplay();

	void setHealthPercentage(float healthPercentage);
	int getHealthPercentage();

private:
	Sprite* background;
	Sprite* bar;
	SDL_Rect* bar_clip;

	Text* fuhealthAmount_;

	float healthPercentage_;
};

