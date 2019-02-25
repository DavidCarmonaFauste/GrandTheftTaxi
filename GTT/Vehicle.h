#pragma once
#include "Container.h"
#include "PhysicObject.h"
#include <Box2D/Box2D.h>
#include "Animation.h"
#include "Resources.h"
#include <vector>

using namespace std;

class Turret;

class Vehicle :
	public Container
{
public:
	Vehicle( Resources::VehicleId id);
	virtual ~Vehicle();
protected:

	double maxSpeed_;
	double maxBackwardSpeed_;
	double turnSpeed_;

	Turret* currentTurret_;
	PhysicObject* phyO_;
	Animation* sprite_;
};
