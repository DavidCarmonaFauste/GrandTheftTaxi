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

	Health* getHealthComponent();

	virtual void Shoot();
	virtual void EquipTurret(Turret* turret);
	virtual void setPosition(const Vector2D &pos, bool force = false) override;

protected:
	PhysicObject* phyO_;
	Animation* sprite_;


	Turret* currentTurret_;
	Health* health_;
};
