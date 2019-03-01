#include "Vehicle.h"


Vehicle::Vehicle(int x, int y, Resources::VehicleId idv, Resources::KeyBindingsId idk) {

	Resources::VehicleInfo& r = Resources::vehicles_[idv];
	this->setPosition(Vector2D(x, y));
	this->setWidth(r.width);
	this->setHeight(r.height);
	this->maxSpeed_ = r.velMax;
	this->maxBackwardSpeed_ = r.velBackwardMax;
	this->turnSpeed_ = r.turnSpeed;
	this->acceleration_ = r.acceleration;
	
	phyO_ = new PhysicObject (b2_dynamicBody , r.width, r.height, position_.x, position_.y);
	this->addLogicComponent(phyO_);
	//inputMov_ = new InputMovement(idk, this);
	//this->addInputComponent(inputMov_);
	//this->addLogicComponent(inputMov_);
	sprite_ = new Animation();
	sprite_->loadAnimation(r.idlePath, "idle");
	sprite_->playAnimation("idle");
	this->addRenderComponent(sprite_);

	phyO_->getBody()->SetTransform(phyO_->getBody()->GetTransform().p, 50);
}


Vehicle::~Vehicle() {

}

PhysicObject * Vehicle::GetPhyO()
{
	return phyO_;
}

float32 Vehicle::GetMaxSpeed()
{
	return maxSpeed_;
}

float32 Vehicle::GetMaxBackwardSpeed()
{
	return maxBackwardSpeed_;
}

float32 Vehicle::GetTurnSpeed()
{
	return turnSpeed_;
}

float32 Vehicle::GetAcceleration()
{
	return acceleration_;
}

