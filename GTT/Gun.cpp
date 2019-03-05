#include "Gun.h"
#include "LinearSC.h"
#include "Animation.h"
#include "Reticule.h"


Gun::Gun(Vehicle* car, ProyectilePool* bPool):Turret(car, bPool)
{
	maxAmmo_ = 7;
	cadence_ = 100;
	reloadTime_ = 1500;
	speed_ = 10;
	ammo_ = maxAmmo_;
	path_ = "../Assets/sprites/gun.png";
	shC_ = new LinearSC(bPool_, this);
	height_ = 200;
	width_ = 100;
	animC_->loadAnimation(path_, "idle");
	animC_->playAnimation("idle");
	if (reticule_ != nullptr) {
		reticule_->ChangeReticule("gun");
	}
}



