#include "StaticSC.h"
#include "ProyectilePool.h"
#include "Reticule.h"

void StaticSC::shoot()
{
	if (turret_->GetProyectileType() == STRIKE)
		if (turret_->GetReticule() != nullptr)
			bPool_->addProyectile(turret_->GetReticule()->getPosition(), Vector2D(), turret_->GetProyectileType(), turret_->GetCadence(), turret_->GetDamage());
		else cout << "StaticSC: la reticula es nullptr";

	else if (turret_->GetProyectileType() == FLAME) {
		Proyectile* p;
		p = bPool_->addProyectile(turret_->getPosition(), Vector2D(), turret_->GetProyectileType(), turret_->GetCadence(), turret_->GetDamage());
		p->addLogicComponent(new FollowGameObject(turret_));//no suficiente, tiene que mantener la posicion relativa a la torreta, no estar siempre encima de ella.
	}
}

