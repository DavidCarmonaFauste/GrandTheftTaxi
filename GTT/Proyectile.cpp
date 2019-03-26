#include "Proyectile.h"


Proyectile::Proyectile()
{
	setActive(false);
	animC_ = new Animation();
	addRenderComponent(animC_);
}

void Proyectile::Impact()//que hacer cuando el proyectil colisiona con algo
{
	active_ = false;
}

void Proyectile::SetBirth(double birthTime)
{
	birthTime_ = birthTime;
}


void Proyectile::update(Uint32 time)
{
	if (SDL_GetTicks() - birthTime_ >= lifeTime_) {
		setActive(false);
	}
	Container::update(time);
}

PhysicObject * Proyectile::GetPhyO()
{
	return phyO_;
}

double Proyectile::GetSpeed()
{
	return speed_;
}

