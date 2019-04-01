#pragma once
#include "ShootComponent.h"

class StaticSC : public ShootComponent
{
public:
	StaticSC(Turret* turret) :ShootComponent(turret) {};
	virtual void shoot(ProyectileInfo prType) {};
	virtual void changeProperties(double prop1, int prop2) {};
	virtual ~StaticSC() {};
};

