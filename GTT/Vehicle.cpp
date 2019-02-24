#include "Vehicle.h"


Vehicle::Vehicle(Resources::VehicleId id) {

	Resources::VehicleInfo& r = Resources::vehicles_[id];

	this->setWidth(r.width);
	this->setHeight(r.height);
	phyO_ = new PhysicObject (b2_dynamicBody , r.width, r.height,
							  position_.getX(), position_.getY());
	this->addLogicComponent(phyO_);

	sprite_ = new Animation();
	sprite_->loadAnimation(r.idlePath, "idle");
	sprite_->playAnimation("idle");
	this->addRenderComponent(sprite_);

	phyO_->getBody()->SetTransform(phyO_->getBody()->GetTransform().p, 50);
}


Vehicle::~Vehicle() {

}

