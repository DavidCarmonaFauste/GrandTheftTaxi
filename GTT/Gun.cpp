#include "Gun.h"
#include "LinearSC.h"
#include "Animation.h"
#include "Reticule.h"


Gun::Gun()
{
	maxAmmo_ = 10;
	cadence_ = 150;
	reloadTime_ = 1500;
	speed_ = 1;
	ammo_ = maxAmmo_;
	path_ = "../Assets/sprites/gun.png";
	animationpath_ = "../Assets/sprites/pistola_anim.png";
	shC_ = new LinearSC(this);
	height_ = 150;
	width_ = 75;
	animC_->loadAnimation(animationpath_, "idle", 2, 1);
	animC_->loadAnimation(path_, "default");
	animC_->playAnimation("default");
	Reticule::GetInstance()->ChangeReticule("gun");
}



