#pragma once
#include "ControlType.h"
#include "Resources.h"
#include "Vehicle.h"
class InputMovement :
	public ControlType
{
public:
	InputMovement(Resources::KeyBindingsId id, Vehicle* v);
	virtual ~InputMovement();

	virtual void handleInput(GameObject* o, Uint32 deltaTime, const SDL_Event& event);
	virtual void update(GameObject* o, Uint32 deltaTime);

private:
	Vehicle* v_;
	Resources::KeyBindingsInfo* k_;

	//Input booleans
	bool forwardPressed_;
	bool backwardPressed_;
	bool rightTurnPressed_;
	bool leftTurnPressed_;
	bool handBrakePressed_;

	float targetLateralVelocity = 0;
	float targetDamping = 1;

	void steeringWheel();
	bool isMoving();
	Vector2D getLateralVelocity();

	void updateFriction();
};

