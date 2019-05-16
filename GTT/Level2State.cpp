#include "Level2State.h"

#include "Turret.h"
#include "ReloadingDisplay.h"
#include "AmmoDisplay.h"

//singleton
#include "Vehicle.h"
#include "ProyectilePool.h"
#include "Reticule.h"
#include "NodeMapsManager.h"
#include "EnemyManager.h"
#include "GameManager.h"
#include "ShopManager.h"

Level2State::Level2State () {}


Level2State::~Level2State () {
	delete tilemap_; tilemap_ = nullptr;
	delete cameraFollow_; cameraFollow_ = nullptr;
}

void Level2State::start () {
	// Taxi	
	Vector2D pos = Vehicle::getInstance ()->getLevel2SpawnPoint ();
	Vehicle::getInstance()->saveSpawnPoint(pos);
	Vehicle::getInstance()->setPosition(pos);
	Vehicle::getInstance()->GetPhyO()->getBody()->SetTransform(pos.Multiply(PHYSICS_SCALING_FACTOR), 0);

	Vehicle::getInstance()->EquipTurret(new Turret(MACHINEGUN));
	Vehicle::getInstance()->EquipTurret(new Turret(SHOTGUN));

	// Tilemap
	NodeMapsManager::getInstance()->ReadNodeMapsInfo();
	EnemyManager::getInstance ()->setLevel ('2');
	EnemyManager::getInstance()->ReadEnemyInfo();

	//Reticule
	Reticule::getInstance()->setPosition(Vehicle::getInstance()->getPosition());

	//Camera logic
	cameraFollow_ = new FollowMiddlePoint(Vehicle::getInstance(), Reticule::getInstance(), GAME_CAMERA, UI_CAMERA, 0.7, 0.25);
	Game::getInstance()->getCamera(GAME_CAMERA)->addLogicComponent(cameraFollow_);

	// Camera positionin
	Vector2D cameraPos = Vehicle::getInstance()->getPosition();
	cameraPos -= Vector2D(Game::getInstance()->getCamera(GAME_CAMERA)->getWidth() / 2,
		Game::getInstance()->getCamera(GAME_CAMERA)->getHeight() / 2);
	Game::getInstance()->getCamera(GAME_CAMERA)->setPosition(cameraPos);


	// Systems
	//...

	// UI
	//...
	Vehicle::getInstance()->getHealthComponent()->registerObserver(UI::getInstance());

	//pushBack GameObj to list
	stage_.push_back(tilemap_);
	stage_.push_back(Vehicle::getInstance());
	stage_.push_back(EnemyManager::getInstance());
	stage_.push_back(GameManager::getInstance());
	stage_.push_back(ShopManager::getInstance());

	stage_.push_back(UI::getInstance());
	stage_.push_back(ProyectilePool::getInstance());
	stage_.push_back(Reticule::getInstance());

	GameManager::getInstance()->setEnemyCount(EnemyManager::getInstance()->getLevel2Enemies());
}

void Level2State::end () {
	EnemyManager::getInstance()->deactivateIA();
}

void Level2State::update (Uint32 deltaTime) {
	Game::getInstance()->getCamera(GAME_CAMERA)->setCentered(true);
	Game::getInstance()->getCamera(UI_CAMERA)->setCentered(true);

	GameState::update(deltaTime);
}

void Level2State::loadTilemap () {
	tilemap_ = new TileMap(PATH_LEVEL_2);
}
