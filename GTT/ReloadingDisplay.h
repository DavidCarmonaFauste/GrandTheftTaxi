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
	virtual ~ReloadingDisplay();
	virtual void update(Uint32 deltaTime);


private:
	Sprite* background;
	Sprite* bar;
	Sprite* perfReSegment;
	SDL_Rect* bar_clip;
	double barWidth;

	Vehicle* vehicle_;
};

