#include "InputMovement.h"

InputMovement::InputMovement(KeysScheme k, Vehicle* v)
{
	k_ = k;
	v_ = v;
	//Input booleans
	forwardPressed_ = false;
	backwardPressed_ = false;
	rightTurnPressed_ = false;
	leftTurnPressed_ = false;

	targetDamping = DFLT_DAMPING;
	targetLateralVelocity = DFLT_LATERAL_VELOCITY;

	targetMaxSpeed = v_->GetMaxSpeed();
	v_->GetPhyO()->getBody()->SetAngularDamping(DFLT_ANG_DAMPING);
}


InputMovement::~InputMovement()
{
}

void InputMovement::handleInput(GameObject * o, Uint32 deltaTime, const SDL_Event & event)
{
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == k_.forward) {
			forwardPressed_ = true;
			Event e(this, STARTED_MOVING_FORWARD);
			broadcastEvent(e);
		}
		if (event.key.keysym.sym == k_.backwards) { 
			backwardPressed_ = true; 
			Event e(this, BACK_MOVING_FORWARD);
			broadcastEvent(e);
		}


		if (event.key.keysym.sym == k_.turnRight) rightTurnPressed_ = true;
		if (event.key.keysym.sym == k_.turnLeft) leftTurnPressed_ = true;
		if (event.key.keysym.sym == SDLK_SPACE) handBrakePressed_ = true;
	}
	else if (event.type == SDL_KEYUP) {	
		if (event.key.keysym.sym == k_.forward) {
			forwardPressed_ = false;
			Event e(this, STOPPED_MOVING_FORWARD);
			broadcastEvent(e);
		}
		if (event.key.keysym.sym == k_.backwards) { 
			backwardPressed_ = false; 
			Event e(this, STOPPED_BACK_MOVING_FORWARD);
			broadcastEvent(e);
		}
		if (event.key.keysym.sym == k_.turnRight) rightTurnPressed_ = false;
		if (event.key.keysym.sym == k_.turnLeft) leftTurnPressed_ = false;
		if (event.key.keysym.sym == SDLK_SPACE) handBrakePressed_ = false;
	}
}

void InputMovement::update(GameObject * o, Uint32 deltaTime)
{
	b2Body* body = Vehicle::GetInstance()->GetPhyO()->getBody();
	Vector2D currentDir = Vector2D(cos(body->GetAngle()), sin(body->GetAngle()));
	Vector2D vel = body->GetLinearVelocity();

	// Check the difference beetween car and speed direction to see
	// if it's going forward
	bool isGoingForward = abs(currentDir.Angle(vel)) < M_PI / 2;

	// Forward and backward acceleration
	if (forwardPressed_ && body->GetLinearVelocity().Length() < (targetMaxSpeed)) {
		Vector2D impulse = body->GetMass() * v_->GetAcceleration() * currentDir;
		body->ApplyLinearImpulse(impulse, body->GetWorldCenter(), true);
	}
	else if (backwardPressed_ && 
			 (body->GetLinearVelocity().Length() < v_->GetMaxBackwardSpeed()
			  || isGoingForward)) {
		Vector2D impulse = body->GetMass() * v_->GetAcceleration() * currentDir;
		body->ApplyLinearImpulse(-1 * impulse, body->GetWorldCenter(), true);
	}

	// Handle rotation
	steeringWheel();

	// Handbrake
	if (!handBrakePressed_) {
		targetDamping = DFLT_DAMPING;
		if (targetLateralVelocity > 0)targetLateralVelocity -= (DFLT_LATERAL_VELOCITY * deltaTime / 100);
		targetMaxSpeed = v_->GetMaxSpeed();
	}
	else {
		targetDamping = HBRK_DAMPING;
		targetLateralVelocity = HBRK_LATERAL_VELOCITY;
		targetMaxSpeed -= deltaTime * HBRK_SPEED_DECAY;
	}
	// Update frictions
	updateFriction();
}

void InputMovement::steeringWheel() {
	b2Body* body = Vehicle::GetInstance()->GetPhyO()->getBody();

	float turnSpeed = 0;
	if (backwardPressed_) {
		if (leftTurnPressed_) turnSpeed = v_->GetTurnSpeed();
		else if (rightTurnPressed_) turnSpeed = -v_->GetTurnSpeed();
	}
	else {
		if (handBrakePressed_) {
			if (leftTurnPressed_) turnSpeed = -2* v_->GetTurnSpeed();
			else if (rightTurnPressed_) turnSpeed = 2* v_->GetTurnSpeed();
		}
		else {
			if (leftTurnPressed_) turnSpeed = -v_->GetTurnSpeed();
			else if (rightTurnPressed_) turnSpeed = v_->GetTurnSpeed();
		}
	}

	if (turnSpeed != 0) {
		turnSpeed *= body->GetLinearVelocity().Length() / v_->GetMaxSpeed();
		body->SetAngularVelocity(turnSpeed);
	}
}

Vector2D InputMovement::getLateralVelocity() {
	b2Body* body = Vehicle::GetInstance()->GetPhyO()->getBody();
	Vector2D normal = body->GetWorldVector(Vector2D(0, 1));
	return b2Dot(normal, body->GetLinearVelocity()) * normal;
}

void InputMovement::updateFriction() {
	b2Body* body = Vehicle::GetInstance()->GetPhyO()->getBody();

	body->SetLinearDamping(targetDamping);

	double lateralImpulseModifier = 1 - targetLateralVelocity;
	Vector2D lateralImpulse = lateralImpulseModifier * body->GetMass() * getLateralVelocity().Multiply(-1);
	body->ApplyLinearImpulse(lateralImpulse, body->GetWorldCenter(), false);
} 

bool InputMovement::isMoving() {
	if (abs(Vehicle::GetInstance()->GetPhyO()->getBody()->GetLinearVelocity().Length()) > 0)
		return true;
	else 
		return false;
}