#pragma once
#include "Turret.h"

class ProyectilePool;

class ShootComponent
{
public:
	ShootComponent(Turret* turret);
	virtual void shoot(ProyectileType prType)=0;
	virtual ~ShootComponent();
protected:
	Turret* turret_;
};

