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
	cout << body->GetLinearVelocity().Length() << endl;
	if (backwardPressed_) 
	{
		if (Vector2D(body->GetLinearVelocity()).AreEqual(v_->GetForwardVector()) == 0.0)
			if (-body->GetLinearVelocity().Length() < v_->GetMaxBackwardSpeed()) {
				Vector2D v = v_->GetForwardVector();
				v.Multiply(v_->GetAcceleration());
				body->SetLinearVelocity(body->GetLinearVelocity() - v);
			}
			else;
		else
			if (body->GetLinearVelocity().Length() < v_->GetMaxBackwardSpeed()) {
				Vector2D v = v_->GetForwardVector();
				v.Multiply(v_->GetAcceleration());
				body->SetLinearVelocity(body->GetLinearVelocity() - v);
			}

	}
	if (rightTurnPressed_) {
		if (isMoving()) 
			steeringWheel('R');
	}
	if (leftTurnPressed_) {
		if (isMoving()) 
			steeringWheel('L');
	}

	if (forwardPressed_ && body->GetLinearVelocity().Length() < v_->GetMaxSpeed()) {
		Vector2D v = v_->GetForwardVector();
		v.Multiply(v_->GetAcceleration());
		cout << "Velocity: " << body->GetLinearVelocity().x << " / " << body->GetLinearVelocity().y << endl;
		body->SetLinearVelocity(body->GetLinearVelocity() + v);
		//cout << "Velocity : " << body->GetLinearVelocity().Length();
	}

	if (abs(body->GetLinearVelocity().Length()) < 0.02) {
		body->SetLinearVelocity(Vector2D());
	}
	//cout << "Pos : " << body->GetTransform().p.x << " / " << body->GetTransform().p.y << endl;

}

void InputMovement::steeringWheel(char d) {
	b2Body* body = v_->GetPhyO()->getBody();
	if (d == 'R') {
		//Aply rotation to object
		body->SetTransform(body->GetPosition(), (int)((int)body->GetAngle() + 360 + v_->GetTurnSpeed() * 0.001) % 360);
		//Apply rotation to velocity
		body->SetLinearVelocity(Vector2D(body->GetLinearVelocity()).ApplyRotation(v_->GetTurnSpeed())* 0.001);

	}
	else if (d == 'L') {
		//Aply rotation to object
		body->SetTransform(body->GetPosition(), (int)((int)body->GetAngle() + 360 - v_->GetTurnSpeed()* 0.001) % 360);
		//Apply rotation to velocity
		body->SetLinearVelocity(Vector2D(body->GetLinearVelocity()).ApplyRotation(-v_->GetTurnSpeed()* 0.001));
	}
}

bool InputMovement::isMoving() {
	if (abs(v_->GetPhyO()->getBody()->GetLinearVelocity().Length() > 0.2))
		return true;
	else 
		return false;
}
