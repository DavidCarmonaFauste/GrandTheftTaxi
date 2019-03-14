#pragma once
#include "ShootComponent.h"

class StaticSC : public ShootComponent
{
public:
	StaticSC(Turret* turret) :ShootComponent(turret) {};
	virtual void shoot() {};
	virtual ~StaticSC() {};
};

