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

	if (timer <= 0) pathfinding();
	timer += 1.0 * (deltaTime / 100.0);
	if (!MovementType_ && close[0] != Vector2D(-999, -999))
	{
		if (positionNow_ <= length)
		{
			if (((v_->getPosition().x < (close[positionNow_].x + 100) && v_->getPosition().x >(close[positionNow_].x - 100)) && (v_->getPosition().y < (close[positionNow_].y + 100) && v_->getPosition().y >(close[positionNow_].y - 100))))
			{
				positionNow_++;
			}

			forwardPressed_ = true;
			Event e(this, STARTED_MOVING_FORWARD);
			broadcastEvent(e);

			int angleNow = body->GetAngle() * 180 / 3.14159265359;
			Vector2D distance = Vector2D(abs(v_->getPosition().x - close[positionNow_].x), abs(v_->getPosition().y - close[positionNow_].y));
			int angle = asin(((distance.y / sqrt(pow(distance.x, 2) + pow(distance.y, 2))))) * 180 / 3.14159265359;

			while (angleNow < 0) angleNow += 360;
			while (angleNow > 360) angleNow -= 360;

			rightTurnPressed_ = false;
			leftTurnPressed_ = false;

			if (close[positionNow_].y - close[positionNow_ - 1].y > 0)
			{
				if (close[positionNow_].x - close[positionNow_ - 1].x > 0) angle += 0; //Primer cuadrante
				else angle += 90; //Segundo cuadrante
			}
			else
			{
				if (close[positionNow_].x - close[positionNow_ - 1].x > 0) angle += 270; //Cuarto cuadrante
				else angle += 180; //Tercer cuadrante
			}

			if (!(angleNow < angle + 10 && angleNow > angle - 10))
			{
				if (angleNow <= 90 && angleNow >= 0) //Cuarto Cuadrante
				{
					if (angleNow < angle && angle < 180) rightTurnPressed_ = true;
					else leftTurnPressed_ = true;
				}
				else if (angleNow <= 180 && angleNow > 90) //Tercer Cuadrante
				{
					if (angleNow < angle && angle < 270 && angle > 90) rightTurnPressed_ = true;
					else leftTurnPressed_ = true;
				}
				else if (angleNow <= 270 && angleNow > 180) //Segundo Cuadrante
				{
					if (angleNow < angle && angle < 270 && angle > 90) rightTurnPressed_ = true;
					else leftTurnPressed_ = true;
				}
				else if (angleNow <= 360 && angleNow > 270) //Primer Cuadrante
				{
					if (angleNow > angle && angle < 180) rightTurnPressed_ = true;
					else leftTurnPressed_ = true;
				}
			}
		}
		else
		{
			forwardPressed_ = false;
			Event e(this, STOPPED_MOVING_FORWARD);
			broadcastEvent(e);
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
	bool finish = false;

	Vector2D wall[2] = { Vector2D(1320, 1320), Vector2D(2420, 2420) };

	int tiles = 100;

	int i = 0;

	positionNow_ = 0;

	std::list<Vector2D> open;

	Vector2D vPosition = v_->getPosition();
	close[i] = vPosition;

	Vector2D final = Vector2D(5000, 5000);
	v_->GetAimComponent();
	Vector2D distance = Vector2D(vPosition.x - final.x, vPosition.y - final.y);

	while (!finish)
	{

		if (!(((vPosition.x + tiles) >= wall[0].x) && ((vPosition.x + tiles) <= wall[1].x) && ((vPosition.y - tiles) >= wall[0].y) && ((vPosition.y - tiles) <= wall[1].y)) && !search(close, Vector2D(vPosition.x + tiles, vPosition.y - tiles)))
			open.push_back(Vector2D(vPosition.x + tiles, vPosition.y - tiles)); //right-up -> 0

		if (!(((vPosition.x + tiles) >= wall[0].x) && ((vPosition.x + tiles) <= wall[1].x) && (vPosition.y >= wall[0].y) && (vPosition.y <= wall[1].y)) && !search(close, Vector2D(vPosition.x + tiles, vPosition.y)))
			open.push_back(Vector2D(vPosition.x + tiles, vPosition.y)); //right-middle -> 1

		if (!(((vPosition.x + tiles) >= wall[0].x) && ((vPosition.x + tiles) <= wall[1].x) && ((vPosition.y + tiles) >= wall[0].y) && ((vPosition.y + tiles) <= wall[1].y) && !search(close, Vector2D(vPosition.x + tiles, vPosition.y + tiles))))
			open.push_back(Vector2D(vPosition.x + tiles, vPosition.y + tiles)); //right-down -> 2

		if (!((vPosition.x >= wall[0].x) && (vPosition.x <= wall[1].x) && ((vPosition.y - tiles) >= wall[0].y) && ((vPosition.y - tiles) <= wall[1].y)) && !search(close, Vector2D(vPosition.x, vPosition.y - tiles)))
			open.push_back(Vector2D(vPosition.x, vPosition.y - tiles)); //middle-up -> 3

		if (!((vPosition.x >= wall[0].x) && (vPosition.x <= wall[1].x) && ((vPosition.y + tiles) >= wall[0].y) && ((vPosition.y + tiles) <= wall[1].y)) && !search(close, Vector2D(vPosition.x, vPosition.y + tiles)))
			open.push_back(Vector2D(vPosition.x, vPosition.y + tiles)); //middle-down -> 4

		if (!(((vPosition.x - tiles) >= wall[0].x) && ((vPosition.x - tiles) <= wall[1].x) && ((vPosition.y - tiles) >= wall[0].y) && ((vPosition.y - tiles) <= wall[1].y)) && !search(close, Vector2D(vPosition.x - tiles, vPosition.y - tiles)))
			open.push_back(Vector2D(vPosition.x - tiles, vPosition.y - tiles)); //left-up -> 5

		if (!(((vPosition.x - tiles) >= wall[0].x) && ((vPosition.x - tiles) <= wall[1].x) && (vPosition.y >= wall[0].y) && (vPosition.y <= wall[1].y)) && !search(close, Vector2D(vPosition.x - tiles, vPosition.y)))
			open.push_back(Vector2D(vPosition.x - tiles, vPosition.y)); //left-middle -> 6

		if (!(((vPosition.x - tiles) >= wall[0].x) && ((vPosition.x - tiles) <= wall[1].x) && ((vPosition.y + tiles) >= wall[0].y) && ((vPosition.y + tiles) <= wall[1].y)) && !search(close, Vector2D(vPosition.x - tiles, vPosition.y + tiles)))
			open.push_back(Vector2D(vPosition.x - tiles, vPosition.y + tiles)); //left-down -> 7


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

		if (((vPosition.x < (final.x + tiles) && vPosition.x >(final.x - tiles)) && (vPosition.y < (final.y + tiles) && vPosition.y >(final.y - tiles))) || i > 19)
		{
			length = i;
			finish = true;
		}
	}
	timer = 100;
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
			if (leftTurnPressed_) turnSpeed = -2 * v_->GetTurnSpeed();
			else if (rightTurnPressed_) turnSpeed = 2 * v_->GetTurnSpeed();
		}
		else {
			if (leftTurnPressed_) turnSpeed = -v_->GetTurnSpeed();
			else if (rightTurnPressed_) turnSpeed = v_->GetTurnSpeed();
		}
	}

	if (turnSpeed != 0) {
		turnSpeed *= body->GetLinearVelocity().Length() / v_->GetMaxSpeed();
		if (MovementType_) body->SetAngularVelocity(turnSpeed);
		else body->SetAngularVelocity(turnSpeed * 4);
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