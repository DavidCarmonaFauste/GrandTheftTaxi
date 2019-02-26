#include "Vehicle.h"


Vehicle::Vehicle(Resources::VehicleId id) {
	Resources::VehicleInfo& r = Resources::vehicles_[id];

	this->setWidth(r.width);
	this->setHeight(r.height);

	// Physics
	phyO_ = new PhysicObject (b2_dynamicBody , r.width, r.height,
							  position_.getX(), position_.getY());
	this->addLogicComponent(phyO_);

	// Sprite
	sprite_ = new Animation();
	sprite_->loadAnimation(r.idlePath, "idle");
	sprite_->playAnimation("idle");
	this->addRenderComponent(sprite_);

	// Health
	health_ = new Health();
	addLogicComponent(health_);
}


Vehicle::~Vehicle() {
	delete phyO_; phyO_ = nullptr;
	delete sprite_; sprite_ = nullptr;
	delete currentTurret_; currentTurret_ = nullptr;
	delete health_; health_ = nullptr;
}

