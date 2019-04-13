#pragma once
#include "Car.h"
class Enemy :public Car
{
public:
	Enemy(int x, int y, VehicleInfo r, KeysScheme k);
	virtual ~Enemy();
};

