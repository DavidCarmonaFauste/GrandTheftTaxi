#include "Flame_thrower.h"
#include "StaticSC.h"
#include "Animation.h"
#include "Reticule.h"


Flame_thrower::Flame_thrower()
{
	maxAmmo_ = 0;
	cadence_ = 100;
	reloadTime_ = 0;
	speed_ = 0;
	lifeTime_ = 300;
	prType_ = FLAME;
	path_ = "../Assets/sprites/flame_thrower.png";
	shC_ = new StaticSC(this);
	height_ = 200;
	width_ = 100;
	animC_->loadAnimation(path_, "idle");
	animC_->playAnimation("idle");
	
}


Flame_thrower::~Flame_thrower()
{
}
