#include "MachineGun.h"
#include "LinearSC.h"
#include "Animation.h"
#include "Reticule.h"
#include "ShootIC.h"


MachineGun::MachineGun()
{
	maxAmmo_ = 25;
	cadence_ = 50;
	reloadTime_ = 3000;
	perfRelIni_ = 0.6;
	perfRelSeg_ = 0.2;
	chargeTime_ = 2000;
	normalB = GUNB;
	specialB = SHOTGUNB;
	automatic_ = true;
	magazine_ = new stack<double>[maxAmmo_];
	for (int i = 0; i < maxAmmo_; i++) {
		magazine_->push(1.0);
	}
	path_ = "../Assets/sprites/machine_gun.png";
	reticulesprite_ = "machinegun";
	shC_ = new LinearSC(this);
	height_ = 200;
	width_ = 100;
	animC_->loadAnimation(path_, "default");
	animC_->loadAnimation(path_, "idle");
	animC_->playAnimation("default");
	
}


