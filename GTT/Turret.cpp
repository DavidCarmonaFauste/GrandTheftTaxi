#include "Turret.h"
#include "Animation.h"
#include "ShootComponent.h"
#include "Reticule.h"
#include "AimComponent.h"
#include "ShootIC.h"
#include "ReloadInputComponent.h"
#include "LinearSC.h"
#include "SpreadSC.h"

Turret::Turret(WeaponInfo w)
{
	animC_ = new Animation();
	addRenderComponent(animC_);
	lastTimeShot_ = -1000;
	chargeprogress_ = SDL_GetTicks();
	reloading_ = false;

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
	magazine_ = new stack<double>[maxAmmo_];
	for (int i = 0; i < maxAmmo_; i++) {
		magazine_->push(1.0);
	}


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
	if (Reticule::GetInstance()->GetCurrentSprite() != reticulesprite_)
		Reticule::GetInstance()->ChangeReticule(reticulesprite_);
	Container::update(deltaTime);
	if (reloading_) {
		Reload();
		ResetChargeProgress();
	} 
}

void Turret::AttachToVehicle(Car * car)
{
	car_ = car;

	followC_ = new FollowGameObject(car_);
	
	addLogicComponent(car_->GetAimComponent());
	addLogicComponent(followC_);

	if (dynamic_cast<Vehicle*>(car_)!=nullptr) {
		Vehicle::GetInstance()->GetShootIC()->ChangeInputMode(automatic_);
		addInputComponent(Vehicle::GetInstance()->GetReloadIC());
		addInputComponent(Vehicle::GetInstance()->GetShootIC());
		addLogicComponent(Vehicle::GetInstance()->GetShootIC());
	}
	

}
		


void Turret::Shoot()
{
	if (!magazine_->empty() && !reloading_) {
		if (SDL_GetTicks() - lastTimeShot_ >= cadence_) {
			if (SDL_GetTicks() - chargeprogress_ >= chargeTime_) {
				specialB.damage = magazine_->top()*defaultSpecialDMG_;
				SPshC_->shoot(specialB);
			}
			else {
				normalB.damage = magazine_->top()*defaultNormalDMG_;
				shC_->shoot(normalB);
			}
			magazine_->pop();
			lastTimeShot_ = SDL_GetTicks();
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
