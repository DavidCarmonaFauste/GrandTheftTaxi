#include "InputMovement.h"



InputMovement::InputMovement(Resources::KeyBindingsId id, Vehicle* v)
{
	v_ = v;
	k_ = &Resources::keyBindings_[id];
	throttle_ = false;

	//Input booleans
	forwardPressed_ = false;
	backwardPressed_ = false;
	rightTurnPressed_ = false;
	leftTurnPressed_ = false;
}


InputMovement::~InputMovement()
{
}

void InputMovement::handleInput(GameObject * o, Uint32 deltaTime, const SDL_Event & event)
{
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == k_->forward) forwardPressed_ = true;
		if (event.key.keysym.sym == k_->backwards) backwardPressed_ = true;
		if (event.key.keysym.sym == k_->turnRight) rightTurnPressed_ = true;
		if (event.key.keysym.sym == k_->turnLeft) leftTurnPressed_ = true;
		if (event.key.keysym.sym == SDLK_SPACE) handBrakePressed_ = true;
	}
	else if (event.type == SDL_KEYUP) {
		if (event.key.keysym.sym == k_->forward) forwardPressed_ = false;
		if (event.key.keysym.sym == k_->backwards) backwardPressed_ = false;
		if (event.key.keysym.sym == k_->turnRight) rightTurnPressed_ = false;
		if (event.key.keysym.sym == k_->turnLeft) leftTurnPressed_ = false;
		if (event.key.keysym.sym == SDLK_SPACE) handBrakePressed_ = false;
	}
}

void InputMovement::update(GameObject * o, Uint32 deltaTime)
{
	b2Body* body = v_->GetPhyO()->getBody();
	Vector2D currentDir = Vector2D(cos(body->GetAngle()), sin(body->GetAngle()));

	// Forward and backward acceleration
	if (forwardPressed_ && body->GetLinearVelocity().Length() < v_->GetMaxSpeed()) {
		Vector2D impulse = body->GetMass() * v_->GetAcceleration() * currentDir;
		body->ApplyLinearImpulse(impulse, body->GetWorldCenter(), true);
	}
	else if (backwardPressed_ && body->GetLinearVelocity().Length() < v_->GetMaxBackwardSpeed()) {
		Vector2D impulse = body->GetMass() * v_->GetAcceleration() * currentDir;
		body->ApplyLinearImpulse(-1 * impulse, body->GetWorldCenter(), true);
	}

	// Handle rotation
	steeringWheel();

	// Handbrake
	if (!handBrakePressed_) {
		body->SetLinearDamping(1);
		Vector2D lateralImpulse = body->GetMass() * getLateralVelocity().Multiply(-1);
		body->ApplyLinearImpulse(lateralImpulse, body->GetWorldCenter(), true);
	}
	else
		body->SetLinearDamping(1.5);
}

void InputMovement::steeringWheel() {
	b2Body* body = v_->GetPhyO()->getBody();

	float turnSpeed = 0;
	if (leftTurnPressed_) turnSpeed = -v_->GetTurnSpeed();
	else if (rightTurnPressed_) turnSpeed = v_->GetTurnSpeed();

	if (turnSpeed != 0) {
		turnSpeed *= body->GetLinearVelocity().Length() / v_->GetMaxSpeed();
		body->SetAngularVelocity(turnSpeed);
	}
}

Vector2D InputMovement::getLateralVelocity() {
	b2Body* body = v_->GetPhyO()->getBody();
	Vector2D normal = body->GetWorldVector(Vector2D(0, 1));
	return b2Dot(normal, body->GetLinearVelocity()) * normal;
}

bool InputMovement::isMoving() {
	if (abs(v_->GetPhyO()->getBody()->GetLinearVelocity().Length()) >= 0)
		return true;
	else 
		return false;
}
