#include "Gun.h"
#include "LinearSC.h"
#include "Animation.h"
#include "Reticule.h"


Gun::Gun()
{
	maxAmmo_ = 10;
	cadence_ = 150;
	reloadTime_ = 1500;
	speed_ = 100;
	lifeTime_ = 1000;
	damage_ = 5;
	perfRelIni_ = 0.45;
	perfRelSeg_ = 0.1;
	magazine_ = new stack<double>[maxAmmo_];
	for (int i = 0; i < maxAmmo_; i++) {
		magazine_->push(1.0);
	}
	path_ = "../Assets/sprites/gun.png";
	animationpath_ = "../Assets/sprites/pistola_anim.png";
	reticulesprite_ = "gun";
	shC_ = new LinearSC(this);
	height_ = 150;
	width_ = 75;
	animC_->loadAnimation(animationpath_, "idle", 2, 1);
	animC_->loadAnimation(path_, "default");
	animC_->playAnimation("default");
}



