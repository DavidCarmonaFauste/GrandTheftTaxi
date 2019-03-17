#pragma once
#include "Container.h"
#include "PhysicObject.h"
#include <Box2D/Box2D.h>
#include "Animation.h"
#include "Resources.h"
#include <vector>
#include "Health.h"
#include <math.h> 

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
	virtual void ChangeTurret();
	virtual void setPosition(const Vector2D &pos, bool force = false) override;
	virtual void handleInput(Uint32 time, const SDL_Event& event);
	virtual void update(Uint32 time);
	virtual void render(Uint32 time);

protected:
	static const int MAXTURRETS = 2;
	PhysicObject* phyO_;
	Animation* sprite_;
	AimComponent* aimC_;//forma de apuntar con la torreta (depende de si es Jugador o IA)
	double velMax_ = 4;
	double velMaxMarchaAtras_ = -2.5;
	double aceleracion_ = 0.1;
	double constanteRozamiento_ = 0.02;
	int velGiro_ = 3;
	bool handBrake_ = false;
	double drift_ = 2;
	double min_Velocity = 0.01;
	bool throttle_ = false;
	bool upPressed = false;
	bool downPressed = false;
	bool rightPressed = false;
	bool leftPressed = false;
	bool spacePressed = false;
	double speed_;
	bool isMoving_();
	void frictionalForce();
	void steeringWheel(char d);

	Turret* turrets_[MAXTURRETS];

	int currentTurret_=0;
	Health* health_;
};
