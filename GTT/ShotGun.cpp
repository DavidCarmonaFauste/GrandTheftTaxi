#include "ShotGun.h"
#include "SpreadSC.h"
#include "Animation.h"
#include "Reticule.h"


ShotGun::ShotGun(Vehicle* car, ProyectilePool* bPool):Turret(car, bPool)
{
	maxAmmo_ = 6;
	cadence_ = 900;
	reloadTime_ = 4000;
	speed_ = 1;
	ammo_ = maxAmmo_;
	animationpath_ = "../Assets/sprites/escopeta_anim.png";
	path_ = "../Assets/sprites/shot_gun.png";
	dispersionangle_ = 30;
	numPellets_ = 3;
	shC_ = new SpreadSC(bPool_, this, dispersionangle_, numPellets_);
	height_ = 150;
	width_ = 75;
	animC_->loadAnimation(animationpath_, "idle", 3, 1);
	animC_->loadAnimation(path_, "default");
	animC_->playAnimation("default");
	Reticule::GetInstance()->ChangeReticule("gun");
}


