#include "LinearSC.h"
#include "ProyectilePool.h"

#define PI 3.14159265359


void LinearSC::shoot()
{
	ProyectilePool::GetInstance()->addProyectile(turret_->getCenter(),
		Vector2D(turret_->GetSpeed()*sin(turret_->getRotation()/180.0*PI), -turret_->GetSpeed()*cos(turret_->getRotation()/180.0*PI)),
		turret_->GetProyectileType(), turret_->GetLifeTime(), turret_->GetDamage());
}

