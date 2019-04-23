#include "ShootIC.h"
#include "Turret.h"


ShootIC::ShootIC(int shootkey)
{
	shootkey_ = shootkey;
	
}

void ShootIC::handleInput(GameObject * o, Uint32 deltaTime, const SDL_Event & event)
{
	
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		if (event.button.button == shootkey_) {
			held_ = true;

			Turret* t = static_cast<Turret*>(o);
			if (t != nullptr) {
				int i;//capture index of observer. only for test
				if (!this->isRegistered(t->getTaxiSoundMnr(), i)) {
					this->registerObserver(t->getTaxiSoundMnr());
				}
				t->Shoot();
				if (t->getCrrActionShoot() != -1) {
					TaxiShootEvent e(this, t->getCrrActionShoot()); //send msg_type and capture idProyectileShoot
					broadcastEvent(e);
				}
			}		
		}
	} 
	else if (event.type == SDL_MOUSEBUTTONUP) {
		if (event.button.button == shootkey_) {
			held_ = false;
		}
	}
}

void ShootIC::update(GameObject * o, Uint32 deltaTime)
{
	if (holdToShoot_&& held_) 
		static_cast<Turret*>(o)->Shoot();
}

void ShootIC::ChangeInputMode(bool hold)
{
	holdToShoot_ = hold;
}


ShootIC::~ShootIC()
{
}
