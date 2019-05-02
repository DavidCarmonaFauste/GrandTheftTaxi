#include "MainState.h"

#include "Turret.h"
#include "ReloadingDisplay.h"
#include "AmmoDisplay.h"
#include "FollowMiddlePoint.h"

//singletton
#include "Vehicle.h"
#include "ProyectilePool.h"
#include "Reticule.h"
#include "NodeMapsManager.h"
#include "EnemyManager.h"



MainState::MainState() {}
MainState::~MainState() {
	for (auto o : stage_) {
		delete o; o = nullptr;
	}
	stage_.clear();
}

//start is called when GameStateMachine change state
void MainState::start() {
	// Taxi	
	Vehicle::getInstance()->initAtributtes(THECOOLERTAXI, DEFAULT_KEYS);
	Vehicle::getInstance()->EquipTurret(new Turret(GUN));
	Vehicle::getInstance()->EquipTurret(new Turret(SHOTGUN));

	Vector2D posBefore = Vehicle::getInstance ()->getShopPosition ();

	// Tilemap
	tilemap_ = new TileMap(PATH_LEVEL_1);

	NodeMapsManager::getInstance()->ReadNodeMapsInfo();
	EnemyManager::getInstance()->ReadEnemyInfo();

	if (posBefore != Vector2D (0.0, 0.0)) {
		findClosestShop ();
	}
	//Reticule
	Reticule::getInstance()->setPosition(Vehicle::getInstance()->getPosition());

	//Camera logic
	cameraFollow = new FollowGameObject(Vehicle::getInstance());
	Game::getInstance()->getCamera(GAME_CAMERA)->addLogicComponent(new FollowMiddlePoint(Vehicle::getInstance(), Reticule::getInstance(), GAME_CAMERA, UI_CAMERA, 0.7, 0.25));
	
	// Camera positioning
	Vector2D cameraPos = Vehicle::getInstance()->getPosition();
	cameraPos -= Vector2D(Game::getInstance()->getCamera(GAME_CAMERA)->getWidth()/2,
						  Game::getInstance()->getCamera(GAME_CAMERA)->getHeight()/2);
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
	stage_.push_back(UI::getInstance());
	stage_.push_back(ProyectilePool::getInstance());
	stage_.push_back(Reticule::getInstance());
	
}

void MainState::end()
{
}


void MainState::update (Uint32 deltaTime) {
	Game::getInstance ()->getCamera (GAME_CAMERA)->setCentered (true);
	Game::getInstance ()->getCamera (UI_CAMERA)->setCentered (true);

	GameState::update (deltaTime);
}

void MainState::findClosestShop () {
	Vector2D spawnPos = Vehicle::getInstance()->getSpawnPosition();
	Vector2D pos = Vehicle::getInstance ()->getShopPosition();
	int i = 0;
	float error = 500.0f;

	do {
		spawnPos = Vehicle::getInstance ()->LVL1_GAS_STATION_SPAWNPOINTS[i];
		++i;
	} while (i <= Vehicle::getInstance ()->GAS_STATIONS_NUMBER && (abs(spawnPos.x - pos.x) > error) && (abs(spawnPos.y - pos.y) > error));

	Vehicle::getInstance ()->setPosition (spawnPos);
	Vehicle::getInstance ()->SaveSpawnPoint (spawnPos);
	Vehicle::getInstance()->GetPhyO()->getBody()->SetTransform(spawnPos.Multiply(PHYSICS_SCALING_FACTOR), 0);
	Vehicle::getInstance ()->GetPhyO ()->getBody ()->SetAwake (true);
	Vehicle::getInstance ()->SaveShopPosition (Vector2D (0.0, 0.0));
}


