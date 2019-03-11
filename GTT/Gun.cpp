#include "Gun.h"
#include "LinearSC.h"
#include "Animation.h"
#include "Reticule.h"


Gun::Gun(Vehicle* car, ProyectilePool* bPool):Turret(car, bPool)
{
	maxAmmo_ = 10;
	cadence_ = 150;
	reloadTime_ = 1500;
	speed_ = 5;
	ammo_ = maxAmmo_;
	path_ = "../Assets/sprites/gun.png";
	animationpath_ = "../Assets/sprites/pistola_anim.png";
	shC_ = new LinearSC(bPool_, this);
	height_ = 100;
	width_ = 50;
	animC_->loadAnimation(animationpath_, "idle", 2, 1);
	animC_->loadAnimation(path_, "default");
	animC_->playAnimation("default");
	if (reticule_ != nullptr) {
		reticule_->ChangeReticule("gun");
	}
}



