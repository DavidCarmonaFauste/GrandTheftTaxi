#pragma once
#include "Container.h"
#include "PhysicObject.h"
#include <Box2D/Box2D.h>
#include "Animation.h"

using namespace std;

class Turret;

class Vehicle :
	public Container
{
public:
	Vehicle();
	virtual ~Vehicle();
protected:
	PhysicObject* phyO_;
	Animation* sprite_;
};
