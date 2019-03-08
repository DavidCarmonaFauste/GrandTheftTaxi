#include "LinearSC.h"
#include "ProyectilePool.h"

#define PI 3.14159265359


void LinearSC::shoot()
{
	cout << turret_->getRotation() << " ";
	bPool_->addProyectile(turret_->getPosition(),
		Vector2D(turret_->GetSpeed()*sin(turret_->getRotation()/180.0*PI), -turret_->GetSpeed()*cos(turret_->getRotation()/180.0*PI)),
		turret_->GetProyectileType(), turret_->GetLifeTime(), turret_->GetDamage());
}

