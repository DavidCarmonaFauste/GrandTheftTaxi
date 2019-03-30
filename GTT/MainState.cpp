#include "MainState.h"
#include "ProyectilePool.h"
#include "Reticule.h"
#include "Turret.h"
#include "ReloadingDisplay.h"


MainState::MainState() {
	// Tilemap
	tilemap_ = new TileMap("./../Assets/maps/test.tmx");
	stage_.push_back(tilemap_);

	// Vehicles
	taxi_ = new Vehicle(100, 100, THECOOLERTAXI, DEFAULT_KEYS);
	stage_.push_back(taxi_);
	cameraFollow = new FollowGameObject(taxi_);
	Game::getInstance()->getCamera(GAME_CAMERA)->addLogicComponent(cameraFollow);

	// Systems
	moneySystem = new Money();
	stage_.push_back(moneySystem);

	// UI
	UI_ = new UI();
	taxi_->getHealthComponent()->registerObserver(UI_);
	moneySystem->registerObserver(UI_);
	stage_.push_back(UI_);

	stage_.push_back(ProyectilePool::GetInstance());
	stage_.push_back(Reticule::GetInstance());

	taxi_->EquipTurret(new Turret(MACHINEGUN));
	taxi_->EquipTurret(new Turret(SNIPER));

	UI_->addUIElement(new ReloadingDisplay(taxi_));
}


MainState::~MainState() {
	for (auto o : stage_) {
		delete o; o = nullptr;
	}
	stage_.clear();
}

