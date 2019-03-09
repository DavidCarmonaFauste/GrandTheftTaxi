#include "ShotGun.h"
#include "SpreadSC.h"
#include "Animation.h"
#include "Reticule.h"


ShotGun::ShotGun(Vehicle* car, ProyectilePool* bPool):Turret(car, bPool)
{
	maxAmmo_ = 6;
	cadence_ = 1000;
	reloadTime_ = 4000;
	speed_ = 1;
	ammo_ = maxAmmo_;
	path_ = "../Assets/sprites/shot_gun.png";
	dispersionangle_ = 30;
	numPellets_ = 3;
	shC_ = new SpreadSC(bPool_, this, dispersionangle_, numPellets_);
	height_ = 100;
	width_ = 50;
	animC_->loadAnimation(path_, "idle");
	animC_->playAnimation("idle");
	if (reticule_ != nullptr) {
		reticule_->ChangeReticule("gun");
	}
}

