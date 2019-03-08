#pragma once
#include "Turret.h"

class Flame_thrower : public Turret
{
public:
	Flame_thrower(Vehicle* car, ProyectilePool* bPool);
	virtual ~Flame_thrower();
};

