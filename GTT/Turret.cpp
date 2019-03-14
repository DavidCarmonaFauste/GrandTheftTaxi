#include "Turret.h"
#include "Animation.h"
#include "ShootComponent.h"
#include "Reticule.h"
#include "AimComponent.h"
#include <math.h>
#define PI 3.14159265359

Turret::Turret()
{
	animC_ = new Animation();
	addRenderComponent(animC_);
	lastTimeReloaded_ = -reloadTime_;
	lastTimeShot_ = -cadence_;
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
	if (ammo_ > 0) {
		if (SDL_GetTicks()-lastTimeShot_ >= cadence_) {
			shC_->shoot();
			ammo_--;
			lastTimeShot_ = SDL_GetTicks();
			animC_->playAnimation("idle", 3.5f, false);
		}
	}
}

void Turret::Reload()//tiempo desde que se llamo a reload por primera vez
{
	ammo_ = maxAmmo_;
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
	return ammo_;
}


double Turret::GetLifeTime()
{
	return lifeTime_;
}

Turret::~Turret()
{
	delete followC_;
	delete shC_;
	delete animC_;
}
