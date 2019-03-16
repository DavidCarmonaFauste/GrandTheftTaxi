#include "MainState.h"


MainState::MainState() {
	// Tilemap
	tilemap_ = new TileMap("./../Assets/maps/test.tmx");
	stage_.push_back(tilemap_);

	// Vehicles
	taxi_ = new Vehicle(Resources::getInstance()->Taxi);
	stage_.push_back(taxi_);
	taxi_->setPosition(Vector2D(100, 100), false);

	// UI
	UI_ = new UI();
	taxi_->getHealthComponent()->registerObserver(UI_);
	stage_.push_back(UI_);
}


MainState::~MainState() {

}

