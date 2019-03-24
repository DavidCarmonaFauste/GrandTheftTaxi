#include "Sniper.h"
#include "LinearSC.h"
#include "Animation.h"
#include "Reticule.h"


Sniper::Sniper()
{
	maxAmmo_ = 4;
	cadence_ = 600;
	reloadTime_ = 3000;
	magazine_ = new stack<double>[maxAmmo_];
	for (int i = 0; i < maxAmmo_; i++) {
		magazine_->push(1.0);
	}
	path_ = "../Assets/sprites/sniper.png";
	reticulesprite_ = "sniper";
	shC_ = new LinearSC(this);
	height_ = 200;
	width_ = 100;
	animC_->loadAnimation(path_, "idle");
	animC_->playAnimation("idle");
}


