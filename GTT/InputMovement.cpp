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
	forwardPressed_ = false;
}


InputMovement::~InputMovement()
{
}

void InputMovement::handleInput(GameObject * o, Uint32 deltaTime, const SDL_Event & event)
{
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_UP) forwardPressed_ = true;
		if (event.key.keysym.sym == SDLK_DOWN) backwardPressed_ = true;
		if (event.key.keysym.sym == SDLK_RIGHT) rightTurnPressed_ = true;
		if (event.key.keysym.sym == SDLK_LEFT) leftTurnPressed_ = true;
		//if (event.key.keysym.sym == SDLK_SPACE) handBrakePressed_ = true;
	}
	else if (event.type == SDL_KEYUP) {
		if (event.key.keysym.sym == SDLK_UP) forwardPressed_ = false;
		if (event.key.keysym.sym == SDLK_DOWN) backwardPressed_ = false;
		if (event.key.keysym.sym == SDLK_RIGHT) rightTurnPressed_ = false;
		if (event.key.keysym.sym == SDLK_LEFT) leftTurnPressed_ = false;
		//if (event.key.keysym.sym == SDLK_SPACE) handBrakePressed_ = false;
	}
}

void InputMovement::update(GameObject * o, Uint32 deltaTime)
{
	b2Body* body = v_->GetPhyO()->getBody();
	if (backwardPressed_) {
		if (body->GetLinearVelocity().Length() > v_->GetMaxBackwardSpeed())
			body->SetLinearVelocity(Vector2D(body->GetLinearVelocity()) - v_->GetAcceleration());
	}
	if (rightTurnPressed_) {
		if (isMoving()) 
			steeringWheel('R');
	}
	if (leftTurnPressed_) {
		if (isMoving()) 
			steeringWheel('L');
	}

	if (forwardPressed_ && body->GetLinearVelocity().Length() > v_->GetMaxSpeed())
		body->SetLinearVelocity(Vector2D(body->GetLinearVelocity()) + v_->GetAcceleration());

	if (abs(body->GetLinearVelocity().Length()) < 0.02) {
		body->SetLinearVelocity(Vector2D());
	}
}

void InputMovement::steeringWheel(char d) {
	b2Body* body = v_->GetPhyO()->getBody();
	if (d == 'R') {
		//Aply rotation to object
		body->SetTransform(body->GetPosition(), (int)((int)body->GetAngle() + 360 + v_->GetTurnSpeed()) % 360);
		//Apply rotation to velocity
		body->SetLinearVelocity(Vector2D(body->GetLinearVelocity()).ApplyRotation(v_->GetTurnSpeed()));
	}
	else if (d == 'L') {
		//Aply rotation to object
		body->SetTransform(body->GetPosition(), (int)((int)body->GetAngle() + 360 - v_->GetTurnSpeed()) % 360);
		//Apply rotation to velocity
		body->SetLinearVelocity(Vector2D(body->GetLinearVelocity()).ApplyRotation(-v_->GetTurnSpeed()));
	}
}

bool InputMovement::isMoving() {
	if (abs(v_->GetPhyO()->getBody()->GetLinearVelocity().Length() > 0.2))
		return true;
	else 
		return false;
}
