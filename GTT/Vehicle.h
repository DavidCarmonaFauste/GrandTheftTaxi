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
class ReloadInputComponent;
class ShootIC;

class Vehicle :
	public Container, public Observable
{
public:
	Vehicle( Resources::VehicleId id);
	virtual ~Vehicle();

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
