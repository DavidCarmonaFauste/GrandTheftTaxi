#pragma once

#include "ControlType.h"

#include "Car.h"

using namespace std;

class Turret;

class ReloadInputComponent;
class ShootIC;

class Vehicle :
	public Car
{
public:
	Vehicle(Vehicle&) = delete;
	Vehicle& operator=(const Vehicle&) = delete;

	static Vehicle* GetInstance() {
		if (instance_ == nullptr) {
			instance_ = new Vehicle(100, 100, THECOOLERTAXI, DEFAULT_KEYS);
		}
		return instance_;
	}
	virtual ~Vehicle();

	//Get
	
	float32 GetMaxBackwardSpeed();
	
	float32 GetAcceleration();
	
	

	
	virtual ReloadInputComponent* GetReloadIC();
	virtual ShootIC* GetShootIC();
	virtual void EquipTurret(Turret* turret);
	virtual void ChangeTurret();
	Turret* getCurrentTurret();

	virtual void handleInput(Uint32 time, const SDL_Event& event);
	virtual void render(Uint32 time);
	virtual void update(Uint32 time);

	virtual bool receiveEvent(Event& e);
	

private:
	Vehicle(int x, int y, VehicleInfo r, KeysScheme k);

	float32 maxBackwardSpeed_;
	
	float32 acceleration_;

	ControlType* control_;

	static const int MAXTURRETS = 2;

	
	ReloadInputComponent* reIC_;
	ShootIC* shIC_;
	Turret* turrets_[MAXTURRETS];

	int currentTurret_=0;

	static Vehicle* instance_;

};
