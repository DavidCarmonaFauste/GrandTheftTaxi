#pragma once
#include "Turret.h"
class MachineGun :public Turret
{
public:
	MachineGun(Vehicle* car, ProyectilePool* bPool);
	virtual ~MachineGun() {};
};

