#pragma once
#include "Car.h"
class Enemy :
	public Car
{
public:
	Enemy(int x, int y, VehicleInfo r);
	virtual ~Enemy();
	virtual void render(Uint32 deltatime);
};

