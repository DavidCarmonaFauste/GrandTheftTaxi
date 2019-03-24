#include "LinearSC.h"
#include "ProyectilePool.h"

void LinearSC::shoot()
{
	ProyectilePool::GetInstance()->addProyectile(turret_->getCenter(),
		Vector2D(turret_->GetSpeed()*sin(turret_->getRotation()/180.0*M_PI), -turret_->GetSpeed()*cos(turret_->getRotation()/180.0*M_PI)),
		turret_->GetProyectileType(), turret_->GetLifeTime(), turret_->GetDamage());
}

