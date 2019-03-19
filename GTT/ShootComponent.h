#pragma once
#include "Turret.h"

class ProyectilePool;

class ShootComponent
{
public:
	ShootComponent(Turret* turret);
	virtual void shoot()=0;
	virtual ~ShootComponent();
protected:
	Turret* turret_;
};
