#pragma once
#include "Container.h"
#include "Animation.h"
#include "PhysicObject.h"



enum proyectileType {
	BULLET,
	FLAME,
	STRIKE
};
class Proyectile : public Container
{
public:
	Proyectile();
	virtual void Impact();
	virtual void SetDamage(double damage);
	virtual void SetLifeTime(double lifeTime);
	virtual void SetAnimation(proyectileType type);
	PhysicObject* GetPhyO();
	virtual ~Proyectile() {};
private:
	Animation* animC_;
	PhysicObject* phyO_;
	double damage_;
	double lifeTime_;
	string bulletPath_= "../Assets/sprites/bullet.png";
	string flamePath_;
	string strikePath_;
};

