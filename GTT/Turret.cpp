#include "Turret.h"

#include "Reticule.h"

#include "ShootIC.h"
#include "ReloadInputComponent.h"
#include "LinearSC.h"
#include "SpreadSC.h"

#include "Animation.h"
#include "ShootComponent.h"
#include "AimComponent.h"

Turret::Turret(WeaponInfo w)
{
	animC_ = new Animation();
	addRenderComponent(animC_);
	lastTimeShot_ = -1000;
	chargeprogress_ = SDL_GetTicks();
	reloading_ = false;
	charged_ = false;

	maxAmmo_ = w.maxAmmo;
	cadence_ = w.cadence;
	reloadTime_ = w.reloadTime;
	perfRelIni_ = w.perfRelIni;
	perfRelSeg_ = w.perfRelSeg;
	chargeTime_ = w.chargeTime;
	normalB = w.normalB;
	defaultNormalDMG_ = normalB.damage;
	specialB = w.specialB;
	defaultSpecialDMG_ = specialB.damage;
	path_ = w.idlePath;
	animationpath_ = w.shootPath;
	reticulesprite_ = w.reticuleSprite;
	height_ = w.height;
	width_ = w.width;
	automatic_ = w.automatic;
	chargedShotDelay_ = w.chargedShotDelay;
	magazine_ = new stack<double>[maxAmmo_];
	for (int i = 0; i < maxAmmo_; i++) {
		magazine_->push(1.0);
	}
	sparkleanim_ = new Animation();
	sparkleEffect_.setWidth(50);
	sparkleEffect_.setHeight(50);
	sparkleEffect_.addRenderComponent(sparkleanim_);
	sparkleanim_->loadAnimation("../Assets/sprites/sparkle_anim.png", "sparkle", 3);
	sparkleEffect_.addLogicComponent(new FollowGameObject(this, MIDDLETOP));

	shotanim_ = new Animation();
	shotEffect_.setWidth(50);
	shotEffect_.setHeight(50);
	shotEffect_.addRenderComponent(shotanim_);
	shotanim_->loadAnimation("../Assets/sprites/shot_effect.png", "shot");
	shotEffect_.addLogicComponent(new FollowGameObject(this, MIDDLETOP));

	animC_->loadAnimation(animationpath_, "idle", w.animationFrames, 1);
	animC_->loadAnimation(path_, "default");
	animC_->playAnimation("default");
	switch (w.shootMode1.firemode) {
		case LINEAR:
			shC_ = new LinearSC(this, w.shootMode1.prop1, w.shootMode1.prop2);
			break;
		case SPREAD:
			shC_ = new SpreadSC(this, w.shootMode1.prop1, w.shootMode1.prop2);
			break;
	}
	switch (w.shootMode2.firemode) {
	case LINEAR:
		SPshC_ = new LinearSC(this, w.shootMode2.prop1, w.shootMode2.prop2);
		break;
	case SPREAD:
		SPshC_ = new SpreadSC(this, w.shootMode2.prop1, w.shootMode2.prop2);
		break;
	}
}

void Turret::update(Uint32 deltaTime)
{
	if (SDL_GetTicks() - chargeprogress_ >= chargeTime_) {
		if (!charged_ && !magazine_->empty()) {
			sparkleanim_->playAnimation("sparkle", 6.0f, false);
			charged_ = true;
		}
	}
		

	sparkleEffect_.update(deltaTime);
	shotEffect_.update(deltaTime);

	
	if (Reticule::getInstance()->GetCurrentSprite() != reticulesprite_)
		Reticule::getInstance()->ChangeReticule(reticulesprite_);


	Container::update(deltaTime);


	if (reloading_) {
		Reload();
		ResetChargeProgress();
	} 
}

void Turret::render(Uint32 deltaTime)
{
	Container::render(deltaTime);
	sparkleEffect_.render(deltaTime);
	shotEffect_.render(deltaTime);
}

void Turret::AttachToVehicle(Car * car)
{
	car_ = car;

	followC_ = new FollowGameObject(car_);
	
	addLogicComponent(car_->GetAimComponent());
	addLogicComponent(followC_);

	if (dynamic_cast<Vehicle*>(car_)!=nullptr) {
		Vehicle::getInstance()->GetShootIC()->ChangeInputMode(automatic_);
		addInputComponent(Vehicle::getInstance()->GetReloadIC());
		addInputComponent(Vehicle::getInstance()->GetShootIC());
		addLogicComponent(Vehicle::getInstance()->GetShootIC());
	}
	

}
		


void Turret::Shoot()
{
	if (!magazine_->empty() && !reloading_) {
		int a = SDL_GetTicks() - lastTimeShot_;
		if (a >= cadence_) {
			if (charged_) {
				specialB.damage = magazine_->top()*defaultSpecialDMG_;
				SPshC_->shoot(specialB);
				lastTimeShot_ = SDL_GetTicks() + chargedShotDelay_;
				charged_ = false;
			}
			else {
				normalB.damage = magazine_->top()*defaultNormalDMG_;
				shC_->shoot(normalB);
				lastTimeShot_ = SDL_GetTicks();
			}

			if(!shotanim_->isAnimationPlaying("shot"))
				shotanim_->playAnimation("shot", 3.0f, false);
			
			magazine_->pop();
			animC_->playAnimation("idle", 3.5f, false);
			ResetChargeProgress();
		}
	}
}

void Turret::Reload()
{
	if (SDL_GetTicks() - reloadpressedTime_ >= reloadTime_) {
		while (magazine_->size() != maxAmmo_) {
			magazine_->push(1.0);
		}
		reloading_ = false;
	}
}

void Turret::PerfectReload()
{
	while (magazine_->size() != maxAmmo_) {
		magazine_->push(2.0);
	}
	reloading_ = false;
}

void Turret::CancelReload()
{
	reloading_ = false;
}



void Turret::InitiateReload()
{
	if (!reloading_ && magazine_->size()!=maxAmmo_) {
		reloading_ = true;
		reloadpressedTime_ = SDL_GetTicks();
	}
	else {
		if (GetReloadPercentage() >= perfRelIni_ && GetReloadPercentage() <= perfRelIni_ + perfRelSeg_)
			PerfectReload();
		else
			CancelReload();
	}
	
}


int Turret::GetCadence()
{
	return cadence_;
}

int Turret::GetAmmo()
{
	return magazine_->size();
}

int Turret::GetMaxAmmo()
{
	return maxAmmo_;
}

double Turret::GetReloadPercentage()
{
	if (reloading_) {
		return (double)(SDL_GetTicks() - reloadpressedTime_) / (double)reloadTime_;
	}
	else if(GetAmmo()>0) return 1;
	else return 0;
}

double Turret::GetPerfReloadSeg()
{
	return perfRelSeg_;
}

double Turret::GetPerfReloadIni()
{
	return perfRelIni_;
}

void Turret::ResetChargeProgress()
{
	chargeprogress_ = SDL_GetTicks();
}

string Turret::GetReticule()
{
	return reticulesprite_;
}

bool Turret::isReloading()
{
	return reloading_;
}

bool Turret::isAutomatic()
{
	return automatic_;
}

Turret::~Turret()
{
	delete followC_;
	delete shC_;
	delete SPshC_;
	delete animC_;
	delete magazine_;
}
