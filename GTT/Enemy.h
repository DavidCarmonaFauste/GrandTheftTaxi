#pragma once
#include "Car.h"
#include "Trigger.h"

class Enemy :public Car
{
public:
	Enemy(int x, int y, VehicleInfo r, KeysScheme k);
	virtual void Damage(double damage);
	virtual void Die();
	virtual void update(Uint32 deltaTime);
	virtual ~Enemy();
private:
	bool bodyReadyToDestroy_;
};

