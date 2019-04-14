#include "MainState.h"
#include "ProyectilePool.h"
#include "Reticule.h"
#include "Turret.h"
#include "ReloadingDisplay.h"
#include "AmmoDisplay.h"
#include "FollowMiddlePoint.h"


MainState::MainState() {
	// Tilemap
	//tilemap_ = new TileMap("./../Assets/maps/test.tmx");
	//stage_.push_back(tilemap_);
	
	// Taxi
	stage_.push_back(Vehicle::GetInstance());
	Reticule::GetInstance()->setPosition(Vehicle::GetInstance()->getPosition());
	cameraFollow = new FollowGameObject(Vehicle::GetInstance());
	Game::getInstance()->getCamera(GAME_CAMERA)->addLogicComponent(new FollowMiddlePoint(Vehicle::GetInstance(), Reticule::GetInstance(), GAME_CAMERA, UI_CAMERA, 0.7, 0.25));
	// Enemy1
	enemy1_ = new Enemy(100, 100, ENEMY1, DEFAULT_KEYS);
	stage_.push_back(enemy1_);

	// Systems
	stage_.push_back(Money::getInstance());
	respawner_ = new Respawner(Vehicle::GetInstance()->getHealthComponent());
	Vehicle::GetInstance()->addLogicComponent(respawner_);

	// TESTING THE SHOP TRIGGER
	//new Shop(100, 100, 500, 0);

	// UI
	Vehicle::GetInstance()->getHealthComponent()->registerObserver(UI::getInstance());
	Money::getInstance()->registerObserver(UI::getInstance());
	stage_.push_back(UI::getInstance());

	stage_.push_back(ProyectilePool::GetInstance());
	stage_.push_back(Reticule::GetInstance());

	Vehicle::GetInstance()->EquipTurret(new Turret(MACHINEGUN));
	Vehicle::GetInstance()->EquipTurret(new Turret(SHOTGUN));

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

	cout << Game::getInstance()->getWorld()->GetBodyCount() << endl;
	GameState::update (deltaTime);
}

