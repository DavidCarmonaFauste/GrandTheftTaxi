#include "AirStrike.h"
#include "StaticSC.h"
#include "Animation.h"
#include "Reticule.h"

AirStrike::AirStrike(Vehicle * car, ProyectilePool * bPool):Turret(car, bPool)
{
	maxAmmo_ = 1;
	cadence_ = 600;
	reloadTime_ = 30000;
	speed_ = 0;
	lifeTime_ = 500;
	prType_ = STRIKE;
	ammo_ = maxAmmo_;
	path_ = "../Assets/sprites/air_strike.png";
	shC_ = new StaticSC(bPool_, this);
	height_ = 500;
	width_ = 500;
	animC_->loadAnimation(path_, "idle");
	animC_->playAnimation("idle");
	if (reticule_ != nullptr) {
		reticule_->ChangeReticule("airstrike");
	}
}


