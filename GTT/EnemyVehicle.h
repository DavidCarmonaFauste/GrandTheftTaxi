#pragma once
#include "Container.h"
#include "PhysicObject.h"
#include <Box2D/Box2D.h>
#include "Animation.h"
#include "ControlType.h"
#include "Resources.h"
#include <vector>
#include "Health.h"
#include <cmath> 
#include "Turret.h"
class EnemyVehicle :
	public Container, public Observable
{
public:
	EnemyVehicle(int x, int y, Resources::VehicleId id);
	~EnemyVehicle();

	//Get
	PhysicObject* GetPhyO();
	float32 GetMaxSpeed();
	float32 GetTurnSpeed();
	float32 GetAcceleration();

	Health* getHealthComponent();

	
	virtual void EquipTurret(Turret* turret);
	Turret* getCurrentTurret();
	virtual void setPosition(const Vector2D &pos);
	virtual void handleInput(Uint32 time, const SDL_Event& event);
	virtual void render(Uint32 time);
	virtual void update(Uint32 time);

protected:
	float32 maxSpeed_;
	float32 turnSpeed_;
	float32 acceleration_;

	ControlType* control_;



	PhysicObject* phyO_;
	Animation* sprite_;
	AimComponent* aimC_;//forma de apuntar con la torreta (depende de si es Jugador o IA)
	Health* health_;
	Turret* gun_;
};

