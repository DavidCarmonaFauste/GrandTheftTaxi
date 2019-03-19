#include "ChangeWeaponIC.h"
#include "Vehicle.h"

ChangeWeaponIC::ChangeWeaponIC(SDL_Keycode changekey)
{
	changekey_ = changekey;
}

ChangeWeaponIC::~ChangeWeaponIC()
{
}

void ChangeWeaponIC::handleInput(GameObject * o, Uint32 deltaTime, const SDL_Event & event)
{

	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == changekey_) {
			static_cast<Vehicle*>(o)->ChangeTurret();
		}
	}
}