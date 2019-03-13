#pragma once
#include "ShootComponent.h"

class StaticSC : public ShootComponent
{
public:
	StaticSC(ProyectilePool* bPool, Turret* turret) :ShootComponent(bPool, turret) {};
	virtual void shoot() {};
	virtual ~StaticSC() {};
};

