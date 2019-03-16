#include "AirStrike.h"
#include "StaticSC.h"
#include "Animation.h"
#include "Reticule.h"

AirStrike::AirStrike()
{
	maxAmmo_ = 1;
	cadence_ = 600;
	reloadTime_ = 30000;
	speed_ = 0;
	lifeTime_ = 500;
	prType_ = STRIKE;
	magazine_ = new stack<double>[maxAmmo_];
	for (int i = 0; i < maxAmmo_; i++) {
		magazine_->push(1.0);
	}
	path_ = "../Assets/sprites/air_strike.png";
	shC_ = new StaticSC(this);
	height_ = 500;
	width_ = 500;
	animC_->loadAnimation(path_, "idle");
	animC_->playAnimation("idle");
	
}


