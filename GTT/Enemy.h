#pragma once
#include "Car.h"
class Enemy :
	public Car
{
public:
	Enemy(VehicleInfo r, KeysScheme k);
	virtual ~Enemy();
	virtual void render(Uint32 deltatime);
};

