#include "PhysicObject.h"


PhysicObject::PhysicObject(b2BodyType type, int w, int h, int x, int y)
{
	visualSize_ = Vector2D(w, h);

	bodyDef_ = b2BodyDef();
	bodyDef_.position.Set(x * Resources::physicsScalingFactor + (w / 2 * Resources::physicsScalingFactor),
						  y * Resources::physicsScalingFactor + (h / 2 * Resources::physicsScalingFactor));
	bodyDef_.type = type;
	body_ = Game::GetWorld()->CreateBody(&bodyDef_);

	fixtureDef_ = b2FixtureDef();
	shape_.SetAsBox(w/2 * Resources::physicsScalingFactor,
					h/2 * Resources::physicsScalingFactor);
	fixtureDef_.shape = &shape_;
	fixtureDef_.density = 1;
	body_->CreateFixture(&fixtureDef_);

}


PhysicObject::~PhysicObject() {

}

void PhysicObject::update(GameObject * o, Uint32 deltaTime) {
	Vector2D nextPos = Vector2D(body_->GetPosition().x,
								body_->GetPosition().y) / Resources::physicsScalingFactor;

	o->setPosition(nextPos - visualSize_/2);

	o->setRotation(body_->GetAngle() * 180/M_PI);
	o->setVelocity(Vector2D(body_->GetLinearVelocity().x, body_->GetLinearVelocity().y)
				   / Resources::physicsScalingFactor);
}

b2Body * PhysicObject::getBody()
{
	return body_;
}
