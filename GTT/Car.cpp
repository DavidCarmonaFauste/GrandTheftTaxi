#include "Car.h"
#include "AimComponent.h"


Car::Car()
{
}


Car::~Car()
{
}

Health * Car::getHealthComponent() {
	return health_;
}

AimComponent * Car::GetAimComponent()
{
	return aimC_;
}

void Car::setPosition(const Vector2D & pos, bool force) {
	GameObject::setPosition(pos);

	if (force) {
		b2Vec2 nextPos = b2Vec2(pos.x, pos.y) +
			b2Vec2(phyO_->getOrigin().x * width_,
				phyO_->getOrigin().y * height_);

		nextPos = b2Vec2(nextPos.x * PHYSICS_SCALING_FACTOR,
			nextPos.y * PHYSICS_SCALING_FACTOR);

		phyO_->getBody()->SetTransform(nextPos, phyO_->getBody()->GetAngle());
	}
}


PhysicObject * Car::GetPhyO()
{
	return phyO_;
}

float32 Car::GetMaxSpeed()
{
	return maxSpeed_;
}

float32 Car::GetTurnSpeed()
{
	return turnSpeed_;
}