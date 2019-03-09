#pragma once
#include "Container.h"
#include "PhysicObject.h"
#include <Box2D/Box2D.h>
#include "Animation.h"
#include "ControlType.h"
#include "Resources.h"
#include <vector>

using namespace std;

class Turret;

class Vehicle :
	public Container
{
public:
	Vehicle(int x, int y, Resources::VehicleId id, Resources::KeyBindingsId idk, Vector2D forwardVector);
	virtual ~Vehicle();

	//Get
	PhysicObject* GetPhyO();
	float32 GetMaxSpeed();
	float32 GetMaxBackwardSpeed();
	float32 GetTurnSpeed();
	float32 GetAcceleration();
	Vector2D GetForwardVector();
	void SetForwardVector(Vector2D forwardVector);

protected:
	Vector2D forwardVector_;
	float32 maxSpeed_;
	float32 maxBackwardSpeed_;
	float32 turnSpeed_;
	float32 acceleration_;

	ControlType* control_;
	Turret* currentTurret_;
	PhysicObject* phyO_;
	Animation* sprite_;
};
