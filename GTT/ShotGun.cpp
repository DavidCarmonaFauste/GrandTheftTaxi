#include "ShotGun.h"
#include "SpreadSC.h"
#include "Animation.h"
#include "Reticule.h"


ShotGun::ShotGun(Vehicle* car, ProyectilePool* bPool):Turret(car, bPool)
{
	maxAmmo_ = 6;
	cadence_ = 1000;
	reloadTime_ = 4000;
	speed_ = 5;
	ammo_ = maxAmmo_;
	path_ = "../Assets/sprites/shot_gun.png";
	dispersionangle_ = 15;
	numPellets_ = 3;
	shC_ = new SpreadSC(bPool_, this, dispersionangle_, numPellets_);
	height_ = 200;
	width_ = 100;
	animC_->loadAnimation(path_, "idle");
	animC_->playAnimation("idle");
	if (reticule_ != nullptr) {
		reticule_->ChangeReticule("gun");
	}
}

