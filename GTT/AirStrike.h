#pragma once
#include "Turret.h"

class AirStrike : public Turret
{
public:
	AirStrike(Vehicle* car, ProyectilePool* bPool);
	virtual ~AirStrike() {};
};

