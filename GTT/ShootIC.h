#pragma once
#include "InputComponent.h"
class ShootIC :
	public InputComponent
{
public:
	ShootIC(int shootkey=SDL_BUTTON_LEFT);
	virtual void handleInput(GameObject* o, Uint32 deltaTime, const SDL_Event& event);
	virtual ~ShootIC();
private:
	int shootkey_;

};

