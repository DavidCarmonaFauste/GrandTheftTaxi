#include "PhysicObject.h"


PhysicObject::PhysicObject(b2BodyType type, int w, int h, int x, int y, float32 angle, b2Vec2 origin) {
	visualSize_ = Vector2D(w, h);
	origin_ = origin;

	// Body definition and instantiation
	bodyDef_ = b2BodyDef();
	bodyDef_.position.Set(x * Resources::physicsScalingFactor + (w / 2 * Resources::physicsScalingFactor),
						  y * Resources::physicsScalingFactor + (h / 2 * Resources::physicsScalingFactor));
	bodyDef_.type = type;
	body_ = Game::GetWorld()->CreateBody(&bodyDef_);

	// Fixture definition and instantiation
	fixtureDef_ = b2FixtureDef();
	shape_.SetAsBox(w/2 * Resources::physicsScalingFactor,
					h/2 * Resources::physicsScalingFactor,
					origin_, angle);
	fixtureDef_.shape = &shape_;
	fixtureDef_.density = 1;
	body_->CreateFixture(&fixtureDef_);

}


PhysicObject::~PhysicObject() {
	Game::GetWorld()->DestroyBody(body_); body_ = nullptr;
}

void PhysicObject::update(GameObject * o, Uint32 deltaTime) {
	Vector2D nextPos = Vector2D(body_->GetPosition().x,
								body_->GetPosition().y) / Resources::physicsScalingFactor;


	// Set the GameObject position to the physics position
	// Subtract the visual size multiplied by the origin to
	// fix the difference between coordinate system origins
	// (those being the top left corner for SDL and the origin
	// defined by the user for the box2D shape).
	o->setPosition(nextPos - (Vector2D(visualSize_.getX() * origin_.x,
										visualSize_.getY() * origin_.y)));


	o->setRotation(body_->GetAngle() * 180/M_PI);
	o->setVelocity(Vector2D(body_->GetLinearVelocity().x, body_->GetLinearVelocity().y)
				   / Resources::physicsScalingFactor);
}

const b2Vec2 PhysicObject::getOrigin() {
	return origin_;
}

b2Body * PhysicObject::getBody() {
	return body_;
}
