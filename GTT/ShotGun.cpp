#include "ShotGun.h"
#include "SpreadSC.h"
#include "Animation.h"
#include "Reticule.h"


ShotGun::ShotGun()
{
	WeaponInfo w = SHOTGUN;

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
	dispersionangle_ = w.prop1;
	numPellets_ = w.prop2;
	automatic_ = w.automatic;
	magazine_ = new stack<double>[maxAmmo_];
	for (int i = 0; i < maxAmmo_; i++) {
		magazine_->push(1.0);
	}


	animC_->loadAnimation(animationpath_, "idle", 3, 1);
	animC_->loadAnimation(path_, "default");
	animC_->playAnimation("default");
	shC_ = new SpreadSC(this, dispersionangle_, numPellets_);
}

void ShotGun::Shoot()
{
		if (!magazine_->empty() && !reloading_) {
			if (SDL_GetTicks() - lastTimeShot_ >= cadence_) {
				if (SDL_GetTicks() - chargeprogress_ >= chargeTime_) {
					shC_->changeProperties(dispersionangle_ * 2, numPellets_ * 2);
					shC_->shoot(specialB);
				}
				else {
					shC_->changeProperties(dispersionangle_, numPellets_);
					shC_->shoot(normalB);
				}
				magazine_->pop();
				lastTimeShot_ = SDL_GetTicks();
				animC_->playAnimation("idle", 3.5f, false);
				ResetChargeProgress();
			}
		}
}




