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
		//if (event.key.keysym.sym == SDLK_SPACE) handBrakePressed_ = true;
	}
	else if (event.type == SDL_KEYUP) {
		if (event.key.keysym.sym == k_->forward) forwardPressed_ = false;
		if (event.key.keysym.sym == k_->backwards) backwardPressed_ = false;
		if (event.key.keysym.sym == k_->turnRight) rightTurnPressed_ = false;
		if (event.key.keysym.sym == k_->turnLeft) leftTurnPressed_ = false;
		//if (event.key.keysym.sym == SDLK_SPACE) handBrakePressed_ = false;
	}
}

void InputMovement::update(GameObject * o, Uint32 deltaTime)
{
	b2Body* body = v_->GetPhyO()->getBody();	
	cout << body->GetAngle() * 180 / M_PI << endl;

	if (backwardPressed_) 
	{
		Vector2D v = body->GetLinearVelocity();
		int degrees = abs(body->GetAngle() * 180 / M_PI);
		degrees = degrees % 360;
		if (degrees <= 180)
			v.x -= (sin(body->GetAngle()));
		else
			v.x -= -abs(sin(body->GetAngle()));
		if (degrees >= 90 && degrees <= 270)
			v.y -= abs(cos(body->GetAngle()));
		else
			v.y -= -abs(cos(body->GetAngle()));

		body->SetLinearVelocity(v);
	}
	if (rightTurnPressed_) {
		if (isMoving()) 
			steeringWheel('R');
	}
	if (leftTurnPressed_) {
		if (isMoving()) 
			steeringWheel('L');
	}

	if (forwardPressed_ /*&& abs(body->GetLinearVelocity().Length()) < v_->GetMaxSpeed()*/) {

		Vector2D v = body->GetLinearVelocity();
		int degrees = abs(body->GetAngle() * 180 / M_PI);
		degrees = degrees % 360;
		if (degrees <= 180)
			v.x = (v.x + v_->GetAcceleration()) * (sin(body->GetAngle()));
		else
			v.x = (v.x + v_->GetAcceleration()) * -abs(sin(body->GetAngle()));
		if (degrees >= 90 && degrees <= 270)
			v.y = (v.y + v_->GetAcceleration()) * abs(cos(body->GetAngle()));
		else
			v.y = (v.y + v_->GetAcceleration()) * -abs(cos(body->GetAngle()));

		body->SetLinearVelocity(v);
	}

}

void InputMovement::steeringWheel(char d) {
	b2Body* body = v_->GetPhyO()->getBody();
	if (d == 'R') {
		//Aply rotation to object
		body->SetAngularVelocity(v_->GetTurnSpeed());
	}
	else if (d == 'L') {
		//Aply rotation to object
		body->SetAngularVelocity(- v_->GetTurnSpeed());
	}
}

bool InputMovement::isMoving() {
	if (abs(v_->GetPhyO()->getBody()->GetLinearVelocity().Length()) >= 0)
		return true;
	else 
		return false;
}
