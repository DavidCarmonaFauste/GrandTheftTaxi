#include "Vehicle.h"
#include "Turret.h"

Vehicle::Vehicle(Resources::VehicleId id) {
	Resources::VehicleInfo& r = Resources::vehicles_[id];

	this->setWidth(r.width);
	this->setHeight(r.height);

	setPosition(Vector2D(100, 0));

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

void Vehicle::Shoot()
{
	currentTurret_->Shoot();
}

void Vehicle::EquipTurret(Turret * turret)
{
	currentTurret_ = turret;
}

void Vehicle::setPosition(const Vector2D & pos, bool force) {
	GameObject::setPosition(pos);

	if (force) {
		b2Vec2 nextPos = b2Vec2(pos.getX(), pos.getY()) + 
						 b2Vec2(phyO_->getOrigin().x * width_,
							   phyO_->getOrigin().y * height_);

		nextPos = b2Vec2(nextPos.x * Resources::physicsScalingFactor,
						 nextPos.y * Resources::physicsScalingFactor);

		phyO_->getBody()->SetTransform(nextPos, phyO_->getBody()->GetAngle());
	}
}

