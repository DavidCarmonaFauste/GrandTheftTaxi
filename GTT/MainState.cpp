#include "MainState.h"
#include "ProyectilePool.h"
#include "Reticule.h"
#include "Turret.h"
#include "ReloadingDisplay.h"
#include "AmmoDisplay.h"
#include "FollowMiddlePoint.h"


//al iniciar la aplicación GameStateMachine construye los estados, por eso no puede iniciar en su constructora.
//se debe llamar a start al cambiar estado
MainState::MainState() {
	

}


MainState::~MainState() {
	for (auto o : stage_) {
		delete o; o = nullptr;
	}
	stage_.clear();
}

//start es llamado cuando se cambia de estado.
void MainState::start()
{
	// Tilemap
	tilemap_ = new TileMap(PATH_LEVEL_1);
	stage_.push_back(tilemap_);

	// Taxi	
	Vehicle::GetInstance()->setPosition(Vector2D(1500, 1000)); //Set position
	stage_.push_back(Vehicle::GetInstance());
	
	
	cameraFollow = new FollowGameObject(Vehicle::GetInstance());
	Game::getInstance()->getCamera(GAME_CAMERA)->addLogicComponent(new FollowMiddlePoint(Vehicle::GetInstance(), Reticule::GetInstance(), GAME_CAMERA, UI_CAMERA, 0.7, 0.25));
	
	Vehicle::GetInstance()->EquipTurret(new Turret(MACHINEGUN));
	Vehicle::GetInstance()->EquipTurret(new Turret(GUN));
	

	stage_.push_back(ProyectilePool::GetInstance());
	
	//Reticule
	Reticule::GetInstance()->setPosition(Vehicle::GetInstance()->getPosition());
	stage_.push_back(Reticule::GetInstance());

	// Enemy1
	//enemy1_ = new Enemy(100, 100, ENEMY1, DEFAULT_KEYS);
	//stage_.push_back(enemy1_);


	// Systems
	moneySystem = new Money();
	stage_.push_back(moneySystem);

	// UI
	UI_ = new UI();
	Vehicle::GetInstance()->getHealthComponent()->registerObserver(UI_);
	moneySystem->registerObserver(UI_);
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

