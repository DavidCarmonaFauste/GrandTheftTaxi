#pragma once
#include "InputComponent.h"
#include "Resources.h"
#include "PhysicObject.h"
class InputMovement :
	public InputComponent
{
public:
	InputMovement(Resources::KeyBindingsId id, PhysicObject* p);
	virtual ~InputMovement();

	virtual void handleInput(GameObject* o, Uint32 deltaTime, const SDL_Event& event);

private:
	PhysicObject* p_;
	bool throttle_;
	Resources::KeyBindingsTnfo* k_;
};

