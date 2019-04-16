#pragma once
#include "Car.h"
#include "Trigger.h"

class Enemy :public Car
{
public:
	Enemy(int x, int y, VehicleInfo r);
	virtual void Damage(double damage);
	virtual void Die();
	virtual void update(Uint32 deltaTime);
	virtual void handleInput(Uint32 deltaTime, const SDL_Event& event);

	virtual ~Enemy();
private:
	bool bodyReadyToDestroy_;
	bool destinated_;
	Vector2D destination_;
	Vector2D direction_;
	Vector2D route[4] = {Vector2D(0,0), Vector2D(400,0), Vector2D(400, 400), Vector2D(0, 400)};
	int node = -1;
	int speed_;
};

