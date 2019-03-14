#include "MachineGun.h"
#include "LinearSC.h"
#include "Animation.h"
#include "Reticule.h"


MachineGun::MachineGun()
{
	maxAmmo_ = 25;
	cadence_ = 50;
	reloadTime_ = 3000;
	speed_ = 10;
	ammo_ = maxAmmo_;
	path_ = "../Assets/sprites/machine_gun.png";
	shC_ = new LinearSC(this);
	height_ = 200;
	width_ = 100;
	animC_->loadAnimation(path_, "idle");
	animC_->playAnimation("idle");
	
}

