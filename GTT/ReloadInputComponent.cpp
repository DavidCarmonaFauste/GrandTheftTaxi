#include "ReloadInputComponent.h"
#include "Vehicle.h"
#include "Turret.h"


ReloadInputComponent::ReloadInputComponent(SDL_Keycode reloadkey)
{
	reloadkey_ = reloadkey;
}

void ReloadInputComponent::handleInput(GameObject * o, Uint32 deltaTime, const SDL_Event & event)
{
	auto* x = static_cast<Vehicle*>(o);
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == reloadkey_) {
			 x->getCurrentTurret()->InitiateReload();
		}
	}
}

ReloadInputComponent::~ReloadInputComponent()
{
}
