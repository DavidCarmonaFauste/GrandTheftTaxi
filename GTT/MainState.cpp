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
void MainState::start()
{
	// Tilemap
	//tilemap_ = new TileMap(PATH_LEVEL_1);
	
	// Taxi	
	Vehicle::getInstance()->initAtributtes(THECOOLERTAXI, DEFAULT_KEYS);
	Vehicle::getInstance()->setPosition(Vector2D(1500, 1000)); 
	Vehicle::getInstance()->EquipTurret(new Turret(MACHINEGUN));
	Vehicle::getInstance()->EquipTurret(new Turret(GUN));

	//Enemies
	//...

	//Camera logic
	cameraFollow = new FollowGameObject(Vehicle::getInstance());
	Game::getInstance()->getCamera(GAME_CAMERA)->addLogicComponent(new FollowMiddlePoint(Vehicle::getInstance(), Reticule::getInstance(), GAME_CAMERA, UI_CAMERA, 0.7, 0.25));
	
	//Reticule
	Reticule::getInstance()->setPosition(Vehicle::getInstance()->getPosition());
	
	// Systems
	moneySystem = new Money();
	
	// UI
	UI_ = new UI();
	Vehicle::getInstance()->getHealthComponent()->registerObserver(UI_);
	moneySystem->registerObserver(UI_);
	

	//pushBack GameObj to list
	//stage_.push_back(tilemap_);
	stage_.push_back(Vehicle::getInstance());
	stage_.push_back(ProyectilePool::getInstance());
	stage_.push_back(Reticule::getInstance());
	stage_.push_back(moneySystem);
	stage_.push_back(UI_);

}

void MainState::end()
{
}

void MainState::update (Uint32 deltaTime) {
	Game::getInstance ()->getCamera (GAME_CAMERA)->setCentered (true);
	Game::getInstance ()->getCamera (UI_CAMERA)->setCentered (true);

	GameState::update (deltaTime);
}

