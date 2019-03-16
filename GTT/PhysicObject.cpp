#include "PhysicObject.h"


PhysicObject::PhysicObject(b2BodyType type, int w, int h, int x, int y, float32 angle, Vector2D origin) {
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
	body_->SetLinearVelocity(Vector2D(0.0f, 0.0f));
	body_->SetLinearDamping(2.0f);
	body_->SetAngularDamping(2.0f);
}


PhysicObject::~PhysicObject() {
	Game::GetWorld()->DestroyBody(body_); body_ = nullptr;
}

void PhysicObject::update(GameObject * o, Uint32 deltaTime) {

	Vector2D nextPos = Vector2D(body_->GetPosition().x, body_->GetPosition().y);
	nextPos.Divide(Resources::physicsScalingFactor);

	if (abs(body_->GetLinearVelocity().Length()) < 0.5) {
		body_->SetLinearVelocity(Vector2D());
	}

	if (abs(body_->GetAngularVelocity()) < 0.5) {
		body_->SetAngularVelocity(0);
	}

	// Set the GameObject position to the physics position
	// Subtract the visual size multiplied by the origin to
	// fix the difference between coordinate system origins
	// (those being the top left corner for SDL and the origin
	// defined by the user for the box2D shape	
	o->setPosition(nextPos - (Vector2D(visualSize_.x * origin_.x, visualSize_.y * origin_.y)));
	o->setRotation(body_->GetAngle() * 180 / M_PI);
}

b2Body * PhysicObject::getBody() {
	return body_;
}
