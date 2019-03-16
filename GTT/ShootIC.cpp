#include "ShootIC.h"
#include "Vehicle.h"


ShootIC::ShootIC(int shootkey)
{
	shootkey_ = shootkey;
}

void ShootIC::handleInput(GameObject * o, Uint32 deltaTime, const SDL_Event & event)
{
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		if (event.button.button == shootkey_) {
			static_cast<Vehicle*>(o)->Shoot();
		}
	}
}


ShootIC::~ShootIC()
{
}
