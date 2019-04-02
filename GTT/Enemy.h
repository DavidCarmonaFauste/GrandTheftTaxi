#pragma once
#include "Car.h"
class Enemy :
	public Car
{
public:
	Enemy(int x, int y, EnemyInfo r, KeysScheme k);
	virtual ~Enemy();
	virtual void render(Uint32 deltatime);
};

