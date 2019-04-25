#pragma once
#include "Car.h"
#include "Trigger.h"
#include "NodeMap.h"
#include "IApatrol.h"

class Enemy :public Car
{
public:
	Enemy();
	Enemy(VehicleInfo r, NodeMap* nmap, vector<Node*> route, Vector2D pos);
	virtual void Damage(double damage);
	virtual void Die();
	virtual void update(Uint32 deltaTime);
	virtual void handleInput(Uint32 deltaTime, const SDL_Event& event);
	virtual ~Enemy();
private:
	bool bodyReadyToDestroy_;
	IApatrol* patrolBehaviour_;
	NodeMap* routemap_;
	int speed_;
};

