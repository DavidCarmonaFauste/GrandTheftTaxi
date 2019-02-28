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
	
	/*position_ = position_ + dir_ * velocity_;
	// when exiting from one side appear in the other
	if (position_.getX() >= getGame()->getWindowWidth()) {
		position_.setX(1 - width_);
	}
	else if (position_.getX() + width_ <= 0) {
		position_.setX(getGame()->getWindowWidth());
	}
	if (position_.getY() >= getGame()->getWindowHeight()) {
		position_.setY(1 - height_);
	}
	else if (position_.getY() + height_ <= 0) {
		position_.setY(getGame()->getWindowHeight());
	}

	if (!upPressed)
		frictionalForce();
	else if (velocity_ < velMax_)
		velocity_ = velocity_ + aceleracion_;

	if (abs(velocity_) < min_Velocity) {
		velocity_ = 0;
	}*/

}

void InputMovement::steeringWheel(char d) {
	b2Body* body = v_->GetPhyO()->getBody();
	if (d == 'R') {
		body->SetTransform(body->GetPosition(), (int)((int)body->GetAngle() + 360 + v_->GetTurnSpeed()) % 360);
		//dir_ = dir_.rotate(velGiro_);
	}
	/*else if (d == 'L') {
		rotation_ = ((int)rotation_ + 360 - velGiro_) % 360;
		if (handBrake_) dir_ = dir_.rotate(-(velGiro_ - drift_));
		else dir_ = dir_.rotate(-velGiro_);
	}*/
}

bool InputMovement::isMoving() {
	if (abs(v_->GetPhyO()->getBody()->GetLinearVelocity().Length() > 0.2))
		return true;
	else 
		return false;
}
