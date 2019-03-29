#include "MachineGun.h"
#include "LinearSC.h"
#include "Animation.h"
#include "Reticule.h"
#include "ShootIC.h"


MachineGun::MachineGun()
{
	WeaponInfo w = MACHINEGUN;

	maxAmmo_ = w.maxAmmo;
	cadence_ = w.cadence;
	reloadTime_ = w.reloadTime;
	perfRelIni_ = w.perfRelIni;
	perfRelSeg_ = w.perfRelSeg;
	chargeTime_ = w.chargeTime;
	normalB = w.normalB;
	specialB = w.specialB;
	path_ = w.idlePath;
	animationpath_ = w.shootPath;
	reticulesprite_ = w.reticuleSprite;
	height_ = w.height;
	width_ = w.width;
	automatic_ = w.automatic;
	magazine_ = new stack<double>[maxAmmo_];
	for (int i = 0; i < maxAmmo_; i++) {
		magazine_->push(1.0);
	}


	shC_ = new LinearSC(this);
	animC_->loadAnimation(path_, "default");
	animC_->loadAnimation(path_, "idle");
	animC_->playAnimation("default");
	
}


