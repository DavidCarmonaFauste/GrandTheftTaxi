#pragma once
#include "Container.h"
#include "Animation.h"
#include "NaturalMove.h"

enum projectileType {
	BULLET,
	FLAME,
	STRIKE
};
class Projectile : public Container
{
public:
	Projectile();
	virtual void Impact();
	virtual void SetDamage(double damage);
	virtual void SetLifeTime(double lifeTime);
	virtual void SetAnimation(projectileType type);
	virtual ~Projectile() {};
private:
	Animation* animC_;
	NaturalMove* movC_;
	double damage_;
	double lifeTime_;
	string bulletPath_ = PATH_BULLET;
	string flamePath_;
	string strikePath_;
};

