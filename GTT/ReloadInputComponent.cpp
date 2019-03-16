#include "ReloadInputComponent.h"
#include "Vehicle.h"


ReloadInputComponent::ReloadInputComponent(SDL_Keycode reloadkey)
{
	reloadkey_ = reloadkey;
}

void ReloadInputComponent::handleInput(GameObject * o, Uint32 deltaTime, const SDL_Event & event)
{
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == reloadkey_) {
			static_cast<Vehicle*>(o)->Reload();
		}
	}
}

ReloadInputComponent::~ReloadInputComponent()
{
}
