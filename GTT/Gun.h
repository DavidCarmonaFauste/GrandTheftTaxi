#pragma once
#include "Turret.h"

class Gun : public Turret
{ 
public:
	Gun(Vehicle* car, ProyectilePool* bPool);
	Gun();
	virtual ~Gun() {};
};

