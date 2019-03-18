#pragma once
#include "Container.h"
#include "PhysicObject.h"
#include <Box2D/Box2D.h>
#include "Animation.h"
#include "Resources.h"
#include <vector>
#include "Health.h"
#include <cmath> 

using namespace std;

class Turret;
class AimComponent;

class Vehicle :
	public Container, public Observable
{
public:
	Vehicle( Resources::VehicleId id);
	virtual ~Vehicle();

	Health* getHealthComponent();

	virtual AimComponent* GetAimComponent();
	virtual void Shoot();
	virtual void Reload();
	virtual void EquipTurret(Turret* turret);
	virtual void setPosition(const Vector2D &pos, bool force = false) override;
	virtual void handleInput(Uint32 time, const SDL_Event& event);
	virtual void render(Uint32 time);
	virtual void update(Uint32 time);

protected:
	PhysicObject* phyO_;
	Animation* sprite_;
	AimComponent* aimC_;//forma de apuntar con la torreta (depende de si es Jugador o IA)	

	Turret* currentTurret_;
	Health* health_;
};
