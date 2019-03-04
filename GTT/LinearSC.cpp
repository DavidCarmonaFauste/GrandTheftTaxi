#include "LinearSC.h"
#include "ProyectilePool.h"

void LinearSC::shoot()
{
	bPool_->addProyectile(turret_->getPosition(),
		Vector2D(turret_->GetSpeed()*cos(turret_->getRotation()), turret_->GetSpeed()*sin(turret_->getRotation())),
		turret_->GetProyectileType(), turret_->GetLifeTime(), turret_->GetDamage());
}

