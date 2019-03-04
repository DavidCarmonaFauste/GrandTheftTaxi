#include "ShootComponent.h"


ShootComponent::ShootComponent(ProyectilePool* bPool, Turret* turret)
{
	bPool_ = bPool;
	turret_ = turret;
}


ShootComponent::~ShootComponent()
{
}
