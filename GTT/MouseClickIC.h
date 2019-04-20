#pragma once
#include "InputComponent.h"
#include "ControlType.h"

class MouseClickIC :
	public ControlType {


public:

	//MouseClickIC (const vector<textureInfo>buttonType, int key = SDL_BUTTON_LEFT);
	MouseClickIC(int key = SDL_BUTTON_LEFT);
	virtual ~MouseClickIC ();

	virtual void handleInput(GameObject* o, Uint32 deltaTime, const SDL_Event& event);
	virtual void update(GameObject* o, Uint32 deltaTime){}

	bool isClickEvent();

private:
	int mouseClickKey_;

};

