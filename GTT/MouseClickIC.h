#pragma once
#include "InputComponent.h"

class MouseClickIC :
	public InputComponent {
public:
	MouseClickIC (int key=SDL_BUTTON_LEFT);
	virtual ~MouseClickIC ();

	virtual void handleInput(GameObject* o, Uint32 deltaTime, const SDL_Event& event);

private:
	int mouseClickKey_;
};

