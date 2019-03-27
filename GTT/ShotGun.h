#pragma once
#include "ShootComponent.h"
class ShotGun :public Turret
{
public:
	ShotGun();
	virtual ~ShotGun() {};
	virtual void Shoot();
protected:
	double dispersionangle_;
	int numPellets_;
};

