#pragma once
#include "Container.h"
#include <Box2D/Box2D.h>

using namespace std;

class Turret;

class Vehicle :
	public Container
{
public:
	Vehicle();
	virtual ~Vehicle();
protected:
	b2Body* body;
};
