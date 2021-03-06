#include "MainState.h"

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

MainState::MainState(){}

MainState::~MainState() {
	delete tilemap_; tilemap_ = nullptr;
	delete cameraFollow_; cameraFollow_ = nullptr;
	delete loadScreen_; loadScreen_ = nullptr;
}

// called to initialize
void MainState::start() {
	// Load screen
	if (useLoadScreen_) {
		SDL_RenderClear(Game::getInstance()->getRenderer());
		loadScreen_ = new Sprite(MAIN_TITLE.idlePath);
		loadScreen_->render(Vector2D(0, 0), MAIN_TITLE.width, MAIN_TITLE.height);
		SDL_RenderPresent(Game::getInstance()->getRenderer());
		useLoadScreen_ = false;
	}

	// Taxi	
	Vector2D pos = Vehicle::getInstance ()->getLevel1OpenSpawnPoint ();
	Vehicle::getInstance()->saveSpawnPoint(pos);
	Vehicle::getInstance()->setPosition(pos);
	Vehicle::getInstance()->GetPhyO()->getBody()->SetTransform(pos.Multiply(PHYSICS_SCALING_FACTOR), 0);

	Vehicle::getInstance()->EquipTurret(new Turret(MACHINEGUN));
	Vehicle::getInstance()->EquipTurret(new Turret(SHOTGUN));

	tilemap_->setSleep (false);

	// Enemies
	NodeMapsManager::getInstance()->ReadNodeMapsInfo();
	EnemyManager::getInstance ()->setLevel ('1');
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

	// Barrier
	roadBlocker_ = new RoadBlocker ();

	//pushBack GameObj to list
	stage_.push_back(tilemap_);
	stage_.push_back (roadBlocker_);
	stage_.push_back(Vehicle::getInstance());
	stage_.push_back(EnemyManager::getInstance());
	stage_.push_back(GameManager::getInstance());
	stage_.push_back(ShopManager::getInstance());

	stage_.push_back(UI::getInstance());
	stage_.push_back(ProyectilePool::getInstance());
	stage_.push_back(Reticule::getInstance());

	GameManager::getInstance()->setEnemyCount(EnemyManager::getInstance()->getLevel1Enemies());
	// stage_.push_back(new FuelUpgrade(100, 100, Vehicle::getInstance()->getPosition().x -200, Vehicle::getInstance()->getPosition().y));
}

void MainState::end()
{
	EnemyManager::getInstance()->deactivateIA();
	tilemap_->setSleep (true);
}


void MainState::update(Uint32 deltaTime) {
	//TODO: fix!! ----------------------------------------------------------------------------------
	if (GameManager::getInstance ()->getEnemyCount () == 0) {
		roadBlocker_->removeBlocker ();
		
	}
	
	Game::getInstance()->getCamera(GAME_CAMERA)->setCentered(true);
	Game::getInstance()->getCamera(UI_CAMERA)->setCentered(true);

	GameState::update(deltaTime);
}

void MainState::loadTilemap () {
	tilemap_ = new TileMap(PATH_LEVEL_1_OPEN);
}

void MainState::setLoadScreenActive(bool active) {
	useLoadScreen_ = active;
}


