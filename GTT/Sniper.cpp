#include "Sniper.h"
#include "LinearSC.h"
#include "Animation.h"
#include "Reticule.h"


Sniper::Sniper()
{
	WeaponInfo w = SNIPER;

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


