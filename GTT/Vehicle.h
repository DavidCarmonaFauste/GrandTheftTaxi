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

	//Get
	PhysicObject* GetPhyO();
	float32 GetMaxSpeed();
	float32 GetMaxBackwardSpeed();
	float32 GetTurnSpeed();
	float32 GetAcceleration();

protected:

	float32 maxSpeed_;
	float32 maxBackwardSpeed_;
	float32 turnSpeed_;
	float32 acceleration_;

	Turret* currentTurret_;
	PhysicObject* phyO_;
	Animation* sprite_;
};
