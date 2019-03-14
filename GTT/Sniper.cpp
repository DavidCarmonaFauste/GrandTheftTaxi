#include "Sniper.h"
#include "LinearSC.h"
#include "Animation.h"
#include "Reticule.h"


Sniper::Sniper()
{
	maxAmmo_ = 4;
	cadence_ = 600;
	reloadTime_ = 3000;
	speed_ = 50;
	ammo_ = maxAmmo_;
	path_ = "../Assets/sprites/sniper.png";
	shC_ = new LinearSC(this);
	height_ = 200;
	width_ = 100;
	animC_->loadAnimation(path_, "idle");
	animC_->playAnimation("idle");
}


