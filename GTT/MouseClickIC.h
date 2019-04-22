#pragma once
#include "ControlType.h"

class MouseClickIC :
	public ControlType {


public:
	MouseClickIC(int key = SDL_BUTTON_LEFT);
	virtual ~MouseClickIC ();

	virtual void handleInput(GameObject* o, Uint32 deltaTime, const SDL_Event& event);
	virtual void update(GameObject* o, Uint32 deltaTime){}


private:
	int mouseClickKey_;
};

