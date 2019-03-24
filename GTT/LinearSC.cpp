#include "LinearSC.h"
#include "ProyectilePool.h"

void LinearSC::shoot()
{
	ProyectilePool::GetInstance()->addStandardB(turret_->getCenter(),
		Vector2D(sin(turret_->getRotation()/180.0*M_PI), -cos(turret_->getRotation()/180.0*M_PI)));
}

