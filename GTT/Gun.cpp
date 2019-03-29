#include "Gun.h"
#include "LinearSC.h"
#include "Animation.h"
#include "Reticule.h"


Gun::Gun()
{
	WeaponInfo w = GUN;

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
	

	animC_->loadAnimation(animationpath_, "idle", 2, 1);
	animC_->loadAnimation(path_, "default");
	animC_->playAnimation("default");
	shC_ = new LinearSC(this);
}



