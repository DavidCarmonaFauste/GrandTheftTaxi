#pragma once
#include "Container.h"
#include "Animation.h"
#include "NaturalMove.h"

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
	virtual ~Proyectile() {};
private:
	Animation* animC_;
	NaturalMove* movC_;
	double damage_;
	double lifeTime_;
	string bulletPath_= "../Assets/sprites/Ricardo.jpg";
	string flamePath_;
	string strikePath_;
};

