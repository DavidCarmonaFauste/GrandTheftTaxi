#pragma once
#include "InputComponent.h"
#include "LogicComponent.h"
#include "Resources.h"
#include "Vehicle.h"
class InputMovement :
	public LogicComponent, public InputComponent
{
public:
	InputMovement(Resources::KeyBindingsId id, Vehicle* v);
	virtual ~InputMovement();

	virtual void handleInput(GameObject* o, Uint32 deltaTime, const SDL_Event& event);
	virtual void update(GameObject* o, Uint32 deltaTime);

private:
	Vehicle* v_;
	bool throttle_;
	Resources::KeyBindingsInfo* k_;

	//Input booleans
	bool forwardPressed_;
	bool backwardPressed_;
	bool rightTurnPressed_;
	bool leftTurnPressed_;
	bool handBrakePressed_;

	void steeringWheel(char d);
	bool isMoving();
};

