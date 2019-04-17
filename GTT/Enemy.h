#pragma once
#include "Car.h"
#include "Trigger.h"
#include "NodeMap.h"

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
	bool finished_;
	Vector2D destination_;
	Vector2D direction_;
	NodeMap routemap_;
	Node* node=nullptr;
	int speed_;
};

