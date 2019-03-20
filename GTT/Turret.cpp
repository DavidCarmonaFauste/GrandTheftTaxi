#include "Turret.h"
#include "Animation.h"
#include "ShootComponent.h"
#include "Reticule.h"
#include "AimComponent.h"

Turret::Turret()
{
	animC_ = new Animation();
	addRenderComponent(animC_);
	lastTimeShot_ = -1000;
	reloading_ = false;
}

void Turret::update(Uint32 deltaTime)
{
	Container::update(deltaTime);
	if (reloading_) {
		Reload();
	} 
}

void Turret::AttachToVehicle(Vehicle * car)
{
	car_ = car;

	followC_ = new FollowGameObject(car_);
	aimC_ = car_->GetAimComponent();

	addLogicComponent(aimC_);
	addLogicComponent(followC_);
}
		
proyectileType Turret::GetProyectileType()
{
	return prType_;
}

void Turret::Shoot()//tiempo desde que se disparo la ultima bala
{
	if (!magazine_->empty() && !reloading_) {
		if (SDL_GetTicks()-lastTimeShot_ >= cadence_) {
			shC_->shoot();
			magazine_->pop();
			lastTimeShot_ = SDL_GetTicks();
			animC_->playAnimation("idle", 3.5f, false);
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
	if (!reloading_) {
		reloading_ = true;
		reloadpressedTime_ = SDL_GetTicks();
	}
}



int Turret::GetSpeed()
{
	return this->speed_;
}

double Turret::GetDamage()
{
	return damage_;
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


double Turret::GetLifeTime()
{
	return lifeTime_;
}

string Turret::GetReticule()
{
	return reticulesprite_;
}

bool Turret::isReloading()
{
	return reloading_;
}

Turret::~Turret()
{
	delete followC_;
	delete shC_;
	delete animC_;
}
