#pragma once
#include "Turret.h"

class ProyectilePool;

class ShootComponent
{
public:
	ShootComponent(ProyectilePool* bPool, Turret* turret);
	virtual void shoot()=0;
	virtual ~ShootComponent();
protected:
	ProyectilePool* bPool_;
	Turret* turret_;
};

