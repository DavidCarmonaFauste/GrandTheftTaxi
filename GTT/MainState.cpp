#include "MainState.h"
#include "ProyectilePool.h"
#include "Reticule.h"
#include "Turret.h"
#include "ReloadingDisplay.h"
#include "AmmoDisplay.h"
#include "FollowMiddlePoint.h"


MainState::MainState() {
	// Tilemap
	tilemap_ = new TileMap(PATH_LEVEL_1);
	stage_.push_back(tilemap_);

	// Taxi
	
	stage_.push_back(Vehicle::GetInstance());
	Vehicle::GetInstance ()->setPosition (Vector2D (3200, 2432));
	Reticule::GetInstance()->setPosition(Vehicle::GetInstance()->getPosition());
	cameraFollow = new FollowGameObject(Vehicle::GetInstance());
	Game::getInstance()->getCamera(GAME_CAMERA)->addLogicComponent(new FollowMiddlePoint(Vehicle::GetInstance(), Reticule::GetInstance(), GAME_CAMERA, UI_CAMERA, 0.7, 0.25));
	// Enemy1
	enemy1_ = new Enemy(100, 100, ENEMY1, DEFAULT_KEYS);
	stage_.push_back(enemy1_);


	// Systems
	moneySystem = new Money();
	stage_.push_back(moneySystem);

	// UI
	UI_ = new UI();
	Vehicle::GetInstance()->getHealthComponent()->registerObserver(UI_);
	moneySystem->registerObserver(UI_);
	stage_.push_back(UI_);

	stage_.push_back(ProyectilePool::GetInstance());
	stage_.push_back(Reticule::GetInstance());

	Vehicle::GetInstance()->EquipTurret(new Turret(MACHINEGUN));
	Vehicle::GetInstance()->EquipTurret(new Turret(GUN));



}


MainState::~MainState() {
	for (auto o : stage_) {
		delete o; o = nullptr;
	}
	stage_.clear();
}

void MainState::update (Uint32 deltaTime) {
	Game::getInstance ()->getCamera (GAME_CAMERA)->setCentered (true);
	Game::getInstance ()->getCamera (UI_CAMERA)->setCentered (true);

	GameState::update (deltaTime);
}

