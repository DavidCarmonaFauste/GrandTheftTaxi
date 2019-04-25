#include "MainState.h"

#include "Turret.h"
#include "ReloadingDisplay.h"
#include "AmmoDisplay.h"
#include "FollowMiddlePoint.h"

//singletton
#include "Vehicle.h"
#include "ProyectilePool.h"
#include "Reticule.h"



MainState::MainState() {}
MainState::~MainState() {
	for (auto o : stage_) {
		delete o; o = nullptr;
	}
	stage_.clear();
}

//start is called when GameStateMachine change state
void MainState::start() {
	//Reticule
	Reticule::getInstance()->setPosition(Vehicle::getInstance()->getPosition());
	
	// Taxi	
	Vehicle::getInstance()->initAtributtes(THECOOLERTAXI, DEFAULT_KEYS);
	Vehicle::getInstance()->EquipTurret(new Turret(GUN));
	Vehicle::getInstance()->EquipTurret(new Turret(SHOTGUN));
	
	

	//Enemies
	enemy1_ = new Enemy(ENEMY1);
	enemy1_->setPosition(Vector2D(-400, 200));

	//Camera logic
	cameraFollow = new FollowGameObject(Vehicle::getInstance());
	Game::getInstance()->getCamera(GAME_CAMERA)->addLogicComponent(new FollowMiddlePoint(Vehicle::getInstance(), Reticule::getInstance(), GAME_CAMERA, UI_CAMERA, 0.7, 0.25));

	// Tilemap
	tilemap_ = new TileMap(PATH_LEVEL_1);

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
	stage_.push_back(Reticule::getInstance());
	stage_.push_back(Vehicle::getInstance());
	stage_.push_back(enemy1_);
	//stage_.push_back(UI::getInstance());
	stage_.push_back(ProyectilePool::getInstance());
	
}

void MainState::end()
{
}

void MainState::update (Uint32 deltaTime) {
	Game::getInstance ()->getCamera (GAME_CAMERA)->setCentered (true);
	Game::getInstance ()->getCamera (UI_CAMERA)->setCentered (true);

	GameState::update (deltaTime);
}

