#include "ControlType.h"
#include "Car.h"
#include "TaxiSoundManagerCP.h"
#include "DialoguesManager.h"
#include "EnterShopIC.h"
#include "ChangeWeaponIC.h"

#pragma once

using namespace std;

class Turret;
class ReloadInputComponent;
class ShootIC;

class Vehicle : public Car
{
	//hide copyBuilder and 	assignment operator
	Vehicle(Vehicle &) = delete;
	Vehicle & operator=(const Vehicle &) = delete;

	static unique_ptr<Vehicle > instance_; //ptr instance class


public:
	//builder
	Vehicle();
	virtual ~Vehicle();

	//init singleton class
	inline static void initInstance() {
		if (instance_.get() == nullptr) {
			instance_.reset(new Vehicle());
		}
	}
	//get singleton class
	inline static Vehicle* getInstance() {
		//SDL_assert(instance_.get() != nullptr); //lanza una mensaje con la primera llamada a getInstance, porque devuelve null
		return instance_.get();
	}

	inline static void destroyInstance() {
		instance_.reset();
		instance_.release();
	}

	void initAtributtes(VehicleInfo r, KeysScheme k);


	float32 GetMaxBackwardSpeed();
	float32 GetAcceleration();
	Vector2D getSpawnPosition ();

	virtual ReloadInputComponent* GetReloadIC();
	virtual ShootIC* GetShootIC();
	virtual void EquipTurret(Turret* turret);
	virtual void ChangeTurret();
	Turret* getCurrentTurret();

	virtual void handleInput(Uint32 time, const SDL_Event& event);
	virtual void render(Uint32 time);
	virtual void update(Uint32 time);

	virtual bool receiveEvent(Event& e);
	virtual void saveSpawnPoint(Vector2D spawn);

	void setLevel1SpawnPoint (Vector2D spawn) { level1SpawnPosition_ = spawn; }
	void setLevel1OpenSpawnPoint (Vector2D spawn) { level1OpenSpawnPosition_ = spawn; }
	void setLevel2SpawnPoint (Vector2D spawn) { level2SpawnPosition_ = spawn; }
	Vector2D getLevel1SpawnPoint () { return level1SpawnPosition_; }
	Vector2D getLevel1OpenSpawnPoint () { return level1OpenSpawnPosition_; }
	Vector2D getLevel2SpawnPoint () { return level2SpawnPosition_; }

private:
	void Respawn();

	Vector2D spawnPosition_;
	Vector2D level1SpawnPosition_;
	Vector2D level1OpenSpawnPosition_;
	Vector2D level2SpawnPosition_;

	int currentTurret_;  
	float32 maxBackwardSpeed_;
	float32 acceleration_;
	bool alive_;
	bool zombie_;
	int deathTime_;

	Turret* turrets_[MAXTURRETS];

	//components
	ControlType* control_;
	ReloadInputComponent* reIC_;
	ShootIC* shIC_;
	EnterShopIC* shopIC_;
	ChangeWeaponIC *changeWeaponIC_;

	TaxiSoundManagerCP* smLC_;
};
