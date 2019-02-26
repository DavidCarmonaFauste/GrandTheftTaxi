#pragma once
#include "Container.h"
#include "PhysicObject.h"
#include <Box2D/Box2D.h>
#include "Animation.h"
#include "Resources.h"
#include <vector>
#include "Health.h"


using namespace std;

class Turret;

class Vehicle :
	public Container
{
public:
	Vehicle( Resources::VehicleId id);
	virtual ~Vehicle();
protected:
	PhysicObject* phyO_;
	Animation* sprite_;

	Turret* currentTurret_;
	Health* health_;
};
