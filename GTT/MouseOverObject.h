#pragma once
#include "InputComponent.h"
class MouseOverObject :
	public InputComponent
{
public:
	MouseOverObject();
	virtual ~MouseOverObject();

	virtual void handleInput(GameObject* o, Uint32 deltaTime, const SDL_Event& event);
};

