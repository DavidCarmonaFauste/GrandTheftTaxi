#include "Vehicle.h"



Vehicle::Vehicle() {
	phyO_ = new PhysicObject (b2_dynamicBody , 20, 40);
	this->addLogicComponent(phyO_);

	sprite_ = new Animation();
	sprite_->loadAnimation("../Assets/sprites/default.png", "idle");
	sprite_->playAnimation("idle");
	this->addRenderComponent(sprite_);
}


Vehicle::~Vehicle() {

}

