#include "Turret.h"
#include "Animation.h"
#include "ShootComponent.h"
#include "Reticule.h"
#include "AimComponent.h"

Turret::Turret()
{
	animC_ = new Animation();
	addRenderComponent(animC_);
	lastTimeReloaded_ = -reloadTime_;
	lastTimeShot_ = -cadence_;
	reloading_ = false;
}

void Turret::update(Uint32 deltaTime)
{
	Container::update(deltaTime);
	if (reloading_) {
		Reload();
	} 
	if (shooting_ != -1 && SDL_GetTicks() > shooting_ + waitingShotTime_) {
		Shoot();
		cout << "shoot" << endl;
		shooting_ = -1;
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
	cout << "reloading" << endl;
	if (SDL_GetTicks() - lastTimeReloaded_ >= reloadTime_) {
		cout << "reloaded" << endl;
		while (magazine_->size() != maxAmmo_) {
			magazine_->push(1.0);
		}
		reloading_ = false;
	}
}

void Turret::InitiateReload()
{
	if (!reloading_) {
		reloading_ = true;
		lastTimeReloaded_ = SDL_GetTicks();
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
