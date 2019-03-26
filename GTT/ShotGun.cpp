#include "ShotGun.h"
#include "SpreadSC.h"
#include "Animation.h"
#include "Reticule.h"


ShotGun::ShotGun()
{
	maxAmmo_ = 6;
	cadence_ = 900;
	reloadTime_ = 4000;
	perfRelIni_ = 0.6;
	perfRelSeg_ = 0.2;
	chargeTime_ = 2000;
	normalB = SHOTGUNB;
	specialB = GUNB;
	magazine_ = new stack<double> [maxAmmo_];
	for (int i = 0; i < maxAmmo_; i++) {
		magazine_->push(1.0);
	}
	animationpath_ = "../Assets/sprites/escopeta_anim.png";
	path_ = "../Assets/sprites/shot_gun.png";
	reticulesprite_ = "shotgun";
	dispersionangle_ = 30;
	numPellets_ = 3;
	shC_ = new SpreadSC(this, dispersionangle_, numPellets_);
	height_ = 150;
	width_ = 75;
	animC_->loadAnimation(animationpath_, "idle", 3, 1);
	animC_->loadAnimation(path_, "default");
	animC_->playAnimation("default");
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
				chargeprogress_ = SDL_GetTicks();
			}
		}
}




