#include "Vehicle.h"


Vehicle::Vehicle(Resources::VehicleId id) {
	Resources::VehicleInfo& r = Resources::getInstance()->vehicles_[id];

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
	health_ = new Health(100);
	addLogicComponent(health_);
}


Vehicle::~Vehicle() {
	delete phyO_; phyO_ = nullptr;
	delete sprite_; sprite_ = nullptr;
	delete currentTurret_; currentTurret_ = nullptr;
	delete health_; health_ = nullptr;
}

Health * Vehicle::getHealthComponent() {
	return health_;
}

void Vehicle::setPosition(const Vector2D & pos, bool force) {
	GameObject::setPosition(pos);

	if (force) {
		b2Vec2 nextPos = b2Vec2(pos.getX(), pos.getY()) + 
						 b2Vec2(phyO_->getOrigin().x * width_,
							   phyO_->getOrigin().y * height_);

		nextPos = b2Vec2(nextPos.x * Resources::getInstance()->physicsScalingFactor,
						 nextPos.y * Resources::getInstance()->physicsScalingFactor);

		phyO_->getBody()->SetTransform(nextPos, phyO_->getBody()->GetAngle());
	}
}

