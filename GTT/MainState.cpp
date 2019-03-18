#include "MainState.h"
#include "ProyectilePool.h"
#include "Reticule.h"
#include "Gun.h"
#include "ShotGun.h"

MainState::MainState() {
	// Tilemap
	tilemap_ = new TileMap("./../Assets/maps/test.tmx");
	stage_.push_back(tilemap_);

	// Vehicles
	taxi_ = new Vehicle(Resources::getInstance()->Taxi);
	stage_.push_back(ProyectilePool::GetInstance());
	stage_.push_back(taxi_);

	// Systems
	moneySystem = new Money();
	stage_.push_back(moneySystem);

	// UI
	UI_ = new UI();
	taxi_->getHealthComponent()->registerObserver(UI_);
	moneySystem->registerObserver(UI_);
	stage_.push_back(UI_);

	stage_.push_back(Reticule::GetInstance());

	taxi_->EquipTurret(new ShotGun());
	taxi_->EquipTurret(new Gun());

}


MainState::~MainState() {
	for (auto o : stage_) {
		delete o; o = nullptr;
	}
	stage_.clear();
}

