#pragma once
#include "ControlType.h"


class Button; 

class MouseClickIC :
	public ControlType {

public:
	MouseClickIC(int key = SDL_BUTTON_LEFT);
	virtual ~MouseClickIC ();

	//redefnie el método dado que esta clase sólo usa Button para tratar su input
	virtual void handleInput(GameObject* o, Uint32 deltaTime, const SDL_Event& event);

	virtual void update(GameObject* o, Uint32 deltaTime){}

	void setButton(Button* b);


private:
	Button* b_;
	int mouseClickKey_;
};

