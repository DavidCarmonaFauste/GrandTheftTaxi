#pragma once
#include "Vehicle.h"
#include <list>
#include <vector>
#include <iterator>
#include <algorithm>
#include <thread>
#include <chrono>
#include <functional>

class InputMovement : public ControlType
{
public:
	InputMovement(KeysScheme k , Vehicle* v, bool mt);
	virtual ~InputMovement();

	virtual void handleInput(GameObject* o, Uint32 deltaTime, const SDL_Event& event);
	virtual void pathfinding();
	virtual void update(GameObject* o, Uint32 deltaTime);

private:
	Vehicle* v_;
	KeysScheme k_;
	bool MovementType_; //True = HandleInput  <=====>  False = Pathfinding

	//Input booleans
	bool forwardPressed_;
	bool backwardPressed_;
	bool rightTurnPressed_;
	bool leftTurnPressed_;
	bool handBrakePressed_;

	float targetLateralVelocity = 0;
	float targetDamping = 1;
	float targetMaxSpeed;

	void steeringWheel();
	bool isMoving();
	Vector2D getLateralVelocity();

	bool search(Vector2D l[], Vector2D v);
	Vector2D close[20];
	int positionNow_ = 0;
	float timer = 0;
	Vector2D find(std::list<Vector2D> l, int c);

	void updateFriction();
};

