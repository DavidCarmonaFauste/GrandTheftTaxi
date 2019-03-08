#pragma once
#include "ShootComponent.h"
class ShotGun :public Turret
{
public:
	ShotGun(Vehicle* car, ProyectilePool* bPool);
	virtual ~ShotGun() {};
protected:
	double dispersionangle_;
	int numPellets_;
};

