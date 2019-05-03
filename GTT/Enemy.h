#pragma once
#include "Car.h"
#include "Trigger.h"
#include "NodeMap.h"
#include "IApatrol.h"

class Turret;

class Enemy :public Car
{
public:
	Enemy();
	Enemy(VehicleInfo r, NodeMap* nmap, vector<Node*> route, Vector2D pos, WeaponInfo weapon);
	virtual void Damage(double damage);
	virtual void Die();
	virtual void update(Uint32 deltaTime);
	virtual void render(Uint32 deltaTime);
	virtual void handleInput(Uint32 deltaTime, const SDL_Event& event);
	virtual int getDistanceFromTaxi();
	virtual Turret* getTurret();
	virtual bool taxiOnRange();
	virtual ~Enemy();
private:
	bool bodyReadyToDestroy_;
	IApatrol* patrolBehaviour_;
	NodeMap* routemap_;
	int speed_;
	int pursuitRange_;
	Turret* turret_;

};

