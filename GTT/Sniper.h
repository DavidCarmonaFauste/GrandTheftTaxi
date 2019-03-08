#pragma once
#include "Turret.h"
class Sniper : public Turret
{
public:
	Sniper(Vehicle* car, ProyectilePool* bPool);
	virtual ~Sniper() {};
};

