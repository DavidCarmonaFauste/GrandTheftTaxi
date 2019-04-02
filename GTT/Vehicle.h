#pragma once

#include "ControlType.h"
#include "Car.h"
#include "TaxiSoundManagerCP.h"

using namespace std;

class Turret;

class ReloadInputComponent;
class ShootIC;

class Vehicle :
	public Car
{
public:
	Vehicle(int x, int y, VehicleInfo r, KeysScheme k);
	virtual ~Vehicle();

	//Get
	
	float32 GetMaxBackwardSpeed();
	
	float32 GetAcceleration();
	
	

	
	virtual ReloadInputComponent* GetReloadIC();
	virtual ShootIC* GetShootIC();
	virtual TaxiSoundManagerCP* GetTxSoundManager();
	virtual void EquipTurret(Turret* turret);
	virtual void ChangeTurret();
	Turret* getCurrentTurret();

	virtual void handleInput(Uint32 time, const SDL_Event& event);
	virtual void render(Uint32 time);
	virtual void update(Uint32 time);

	virtual bool receiveEvent(Event& e);
	

protected:
	
	float32 maxBackwardSpeed_;
	
	float32 acceleration_;

	ControlType* control_;

	TaxiSoundManagerCP* smLC_;

	static const int MAXTURRETS = 4;

	
	ReloadInputComponent* reIC_;
	ShootIC* shIC_;

	Turret* turrets_[MAXTURRETS];

	int currentTurret_=0;
	
};
