#include "Turret.h"
#include "Animation.h"
#include "ShootComponent.h"
#include "Reticule.h"
#include <math.h>
#define PI 3.14159265359

Turret::Turret(Vehicle* car, ProyectilePool* bPool)
{
	car_ = car;
	followC_ = new FollowGameObject(car_);
	animC_ = new Animation();
	addLogicComponent(followC_);
	addRenderComponent(animC_);
	bPool_ = bPool;
	reticule_ = new Reticule();
	lastTimeReloaded_ = -reloadTime_;
	lastTimeShot_ = -cadence_;
}

void Turret::render(Uint32 deltaTime)
{
	Container::render(deltaTime);
	if (reticule_ != nullptr)
		reticule_->render(deltaTime);
		
}

void Turret::update(Uint32 deltaTime)
{
	Container::update(deltaTime);
	if (reticule_ != nullptr) {
		reticule_->update(deltaTime);
		double disX = reticule_->getPosition().getX() - position_.getX();
		double disY = reticule_->getPosition().getY() - position_.getY();

		rotation_  = acos(-disY/(sqrt(pow(disX, 2) + pow(disY, 2))));
		rotation_ = rotation_ * 180.0 / PI;

		if (disX < 0) {
			rotation_ = -rotation_;
		}
		
	}
		

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
			cout << ammo_;
			lastTimeShot_ = SDL_GetTicks();
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

Reticule * Turret::GetReticule()
{
	return reticule_;
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
