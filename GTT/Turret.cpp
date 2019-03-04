#include "Turret.h"
#include "Animation.h"
#include "ShootComponent.h"
#include "Reticule.h"

Turret::Turret(Vehicle* car, ProyectilePool* bPool)
{
	car_ = car;
	//followC_ = new FollowComponent(car_);
	animC_ = new Animation();
	addLogicComponent(followC_);
	addRenderComponent(animC_);
	bPool_ = bPool;
	//if (!car->isEnemy())
		//reticule_ = new Reticule();
		
}

Turret::Turret()
{
	car_ = nullptr;
	//followC_ = new FollowComponent(car_);
	animC_ = new Animation();
	addLogicComponent(followC_);
	addRenderComponent(animC_);
	bPool_ = nullptr;
	//reticule_ = new Reticule();
}

void Turret::render(Uint32 deltaTime)
{
	Container::render(deltaTime);
	//if (reticule_ != nullptr)
		//reticule_->render(deltaTime);
		
}

void Turret::update(Uint32 deltaTime)
{
	Container::update(deltaTime);
	if (reticule_ != nullptr)
		//reticule_->update(deltaTime);
		;

}

proyectileType Turret::GetProyectileType()
{
	return prType_;
}

void Turret::Shoot(int deltaTime)//tiempo desde que se disparo la ultima bala
{
	if (ammo_ > 0) {
		if (deltaTime >= cadence_) {
			//shC_->shoot();
			ammo_--;
		}
	}
}

void Turret::Reload(int deltaTime)//tiempo desde que se llamo a reload por primera vez
{
	if (deltaTime >= reloadTime_ && maxAmmo_ > 0) {
		ammo_ = maxAmmo_;
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
