#pragma once
#include "Container.h"
#include "PhysicObject.h"
#include <Box2D/Box2D.h>
#include "Animation.h"
#include "ControlType.h"
#include <vector>
#include "Health.h"
#include <cmath> 

using namespace std;

class Turret;
class AimComponent;
class ReloadInputComponent;
class ShootIC;

class Vehicle :
	public Container, public Observable
{
public:
	Vehicle(int x, int y, VehicleInfo r, KeysScheme k);
	virtual ~Vehicle();

	//Get
	PhysicObject* GetPhyO();
	float32 GetMaxSpeed();
	float32 GetMaxBackwardSpeed();
	float32 GetTurnSpeed();
	float32 GetAcceleration();
	
	Health* getHealthComponent();

	virtual AimComponent* GetAimComponent();
	virtual ReloadInputComponent* GetReloadIC();
	virtual ShootIC* GetShootIC();
	virtual void EquipTurret(Turret* turret);
	virtual void ChangeTurret();
	Turret* getCurrentTurret();
	virtual void setPosition(const Vector2D &pos, bool force = false) override;
	virtual void handleInput(Uint32 time, const SDL_Event& event);
	virtual void render(Uint32 time);
	virtual void update(Uint32 time);

protected:
	float32 maxSpeed_;
	float32 maxBackwardSpeed_;
	float32 turnSpeed_;
	float32 acceleration_;

	ControlType* control_;

	static const int MAXTURRETS = 2;

	PhysicObject* phyO_;
	Animation* sprite_;
	AimComponent* aimC_;//forma de apuntar con la torreta (depende de si es Jugador o IA)	
	ReloadInputComponent* reIC_;
	ShootIC* shIC_;
	Turret* turrets_[MAXTURRETS];

	int currentTurret_=0;
	Health* health_;
};
