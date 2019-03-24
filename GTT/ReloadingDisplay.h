#pragma once
#include "Container.h"
#include "Sprite.h"
#include "Vehicle.h"

class ReloadingDisplay :
	public Container
{
public:
	ReloadingDisplay(Vehicle* vehicle);
	void setReloadingPercentage();
	int getReloadingPercentage();
	virtual ~ReloadingDisplay();
	virtual void update(Uint32 deltaTime);


private:
	Sprite* background;
	Sprite* bar;
	SDL_Rect* bar_clip;

	Vehicle* vehicle_;
};

