#include "InputMovement.h"

InputMovement::InputMovement(KeysScheme k, Vehicle* v, bool mt)
{
	v_ = v;
	k_ = k;
	MovementType_ = mt;
	close[0] = Vector2D(-999, -999);

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
	if (MovementType_)
	{
		if (event.type == SDL_KEYDOWN) {
			if (event.key.keysym.sym == k_.forward) {
				forwardPressed_ = true;
				Event e(this, STARTED_MOVING_FORWARD);
				broadcastEvent(e);
			}
			if (event.key.keysym.sym == k_.backwards) backwardPressed_ = true;
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
			if (event.key.keysym.sym == k_.backwards) backwardPressed_ = false;
			if (event.key.keysym.sym == k_.turnRight) rightTurnPressed_ = false;
			if (event.key.keysym.sym == k_.turnLeft) leftTurnPressed_ = false;
			if (event.key.keysym.sym == SDLK_SPACE) handBrakePressed_ = false;
		}
	}

}

void InputMovement::update(GameObject * o, Uint32 deltaTime)
{
	b2Body* body = v_->GetPhyO()->getBody();
	Vector2D currentDir = Vector2D(cos(body->GetAngle()), sin(body->GetAngle()));
	Vector2D vel = body->GetLinearVelocity();

	if(timer <= 0) pathfinding();
	timer -= 1.0 * (deltaTime/100.0);
	if (!MovementType_ && close[0] != Vector2D(-999, -999))
	{
		if (((v_->getPosition().x < (close[positionNow_].x + 10) && v_->getPosition().x >(close[positionNow_].x - 10)) && (v_->getPosition().y < (close[positionNow_].y + 10) && v_->getPosition().y >(close[positionNow_].y - 10)))) positionNow_++;
		if (v_->getPosition().y > close[positionNow_].y)
		{
			forwardPressed_ = true;
			Event e(this, STARTED_MOVING_FORWARD);
			broadcastEvent(e);
			if (v_->getPosition().x < close[positionNow_].x) rightTurnPressed_ = true;
			if (v_->getPosition().x < close[positionNow_].x) leftTurnPressed_ = true;
		}
		else if (v_->getPosition().y > close[positionNow_].y)
		{
			forwardPressed_ = false;
			Event e(this, STOPPED_MOVING_FORWARD);
			broadcastEvent(e);
			if (v_->getPosition().x < close[positionNow_].x) rightTurnPressed_ = false;
			if (v_->getPosition().x < close[positionNow_].x) leftTurnPressed_ = false;
		}
	}
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

void InputMovement::pathfinding()
{
	timer = 200;
//	Vector2D vPosition = v_->getPosition();
//	Vector2D close[20];
//	
//	thread([close, vPosition, ] {
		bool finish = false;

		Vector2D wall[2] = { Vector2D(320, 320), Vector2D(320, 320) };

		int i = 0;

		std::list<Vector2D> open;

		Vector2D vPosition = v_->getPosition();
		close[i] = vPosition;

		Vector2D final = Vector2D(vPosition.x - 1000, vPosition.y - 500);
		Vector2D distance = Vector2D(vPosition.x - final.x, vPosition.y - final.y);

		while (!finish && i < 20)
		{

			if (!(((vPosition.x + 32) >= wall[0].x) && ((vPosition.x + 32) <= wall[1].x) && ((vPosition.y - 32) >= wall[0].y) && ((vPosition.y - 32) <= wall[1].y)) && !search(close, Vector2D(vPosition.x + 32, vPosition.y - 32)))
				open.push_back(Vector2D(vPosition.x + 32, vPosition.y - 32)); //right-up -> 0

			if (!(((vPosition.x + 32) >= wall[0].x) && ((vPosition.x + 32) <= wall[1].x) && (vPosition.y >= wall[0].y) && (vPosition.y <= wall[1].y)) && !search(close, Vector2D(vPosition.x + 32, vPosition.y)))
				open.push_back(Vector2D(vPosition.x + 32, vPosition.y)); //right-middle -> 1

			if (!(((vPosition.x + 32) >= wall[0].x) && ((vPosition.x + 32) <= wall[1].x) && ((vPosition.y + 32) >= wall[0].y) && ((vPosition.y + 32) <= wall[1].y) && !search(close, Vector2D(vPosition.x + 32, vPosition.y + 32))))
				open.push_back(Vector2D(vPosition.x + 32, vPosition.y + 32)); //right-down -> 2

			if (!((vPosition.x >= wall[0].x) && (vPosition.x <= wall[1].x) && ((vPosition.y - 32) >= wall[0].y) && ((vPosition.y - 32) <= wall[1].y)) && !search(close, Vector2D(vPosition.x, vPosition.y - 32)))
				open.push_back(Vector2D(vPosition.x, vPosition.y - 32)); //middle-up -> 3

			if (!((vPosition.x >= wall[0].x) && (vPosition.x <= wall[1].x) && ((vPosition.y + 32) >= wall[0].y) && ((vPosition.y + 32) <= wall[1].y)) && !search(close, Vector2D(vPosition.x, vPosition.y + 32)))
				open.push_back(Vector2D(vPosition.x, vPosition.y + 32)); //middle-down -> 4

			if (!(((vPosition.x - 32) >= wall[0].x) && ((vPosition.x - 32) <= wall[1].x) && ((vPosition.y - 32) >= wall[0].y) && ((vPosition.y - 32) <= wall[1].y)) && !search(close, Vector2D(vPosition.x - 32, vPosition.y - 32)))
				open.push_back(Vector2D(vPosition.x - 32, vPosition.y - 32)); //left-up -> 5

			if (!(((vPosition.x - 32) >= wall[0].x) && ((vPosition.x - 32) <= wall[1].x) && (vPosition.y >= wall[0].y) && (vPosition.y <= wall[1].y)) && !search(close, Vector2D(vPosition.x - 32, vPosition.y)))
				open.push_back(Vector2D(vPosition.x - 32, vPosition.y)); //left-middle -> 6

			if (!(((vPosition.x - 32) >= wall[0].x) && ((vPosition.x - 32) <= wall[1].x) && ((vPosition.y + 32) >= wall[0].y) && ((vPosition.y + 32) <= wall[1].y)) && !search(close, Vector2D(vPosition.x - 32, vPosition.y + 32)))
				open.push_back(Vector2D(vPosition.x - 32, vPosition.y + 32)); //left-down -> 7


			int minum = 99999;
			int vec_to_close = -1;
			for (int i = 0; i < 8; i++)
			{
				Vector2D actual_Vect = find(open, i);

				int h = abs(actual_Vect.x - final.x) + abs(actual_Vect.y - final.y);
				int g = sqrtf(abs(vPosition.x - actual_Vect.x) + abs(vPosition.y - actual_Vect.y));
				int f = h + g;

				if (f < minum)
				{
					minum = f;
					vec_to_close = i;
				}
			}
			i++;
			close[i] = find(open, vec_to_close);
			vPosition = close[i];

			open.clear();

			if ((vPosition.x < (final.x + 32) && vPosition.x >(final.x - 32)) && (vPosition.y < (final.y + 32) && vPosition.y >(final.y - 32))) finish = true;

		}
	//	this_thread::sleep_for(chrono::seconds(2));
//	}).detach();
}

bool InputMovement::search(Vector2D l[], Vector2D v)
{
	for (int i = 0; i < l->Length(); i++)
	{
		if (l[i] == v) return true;
	}
	return false;
}

Vector2D InputMovement::find(std::list<Vector2D> l, int c)
{
	int i = 0;
	for (auto v : l)
	{
		if (i == c) return v;
		i++;
	}

	return Vector2D(-999, -999);
}

void InputMovement::steeringWheel() {
	b2Body* body = v_->GetPhyO()->getBody();

	float turnSpeed = 0;
	if (backwardPressed_) {
		if (leftTurnPressed_) turnSpeed = v_->GetTurnSpeed();
		else if (rightTurnPressed_) turnSpeed = -v_->GetTurnSpeed();
	}
	else {
		if (handBrakePressed_) {
			if (leftTurnPressed_) turnSpeed = -2*v_->GetTurnSpeed();
			else if (rightTurnPressed_) turnSpeed = 2*v_->GetTurnSpeed();
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
	b2Body* body = v_->GetPhyO()->getBody();
	Vector2D normal = body->GetWorldVector(Vector2D(0, 1));
	return b2Dot(normal, body->GetLinearVelocity()) * normal;
}

void InputMovement::updateFriction() {
	b2Body* body = v_->GetPhyO()->getBody();

	body->SetLinearDamping(targetDamping);

	double lateralImpulseModifier = 1 - targetLateralVelocity;
	Vector2D lateralImpulse = lateralImpulseModifier * body->GetMass() * getLateralVelocity().Multiply(-1);
	body->ApplyLinearImpulse(lateralImpulse, body->GetWorldCenter(), false);
} 

bool InputMovement::isMoving() {
	if (abs(v_->GetPhyO()->getBody()->GetLinearVelocity().Length()) > 0)
		return true;
	else 
		return false;
}