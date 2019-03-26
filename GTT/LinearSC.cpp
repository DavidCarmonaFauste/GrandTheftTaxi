#include "LinearSC.h"
#include "ProyectilePool.h"

void LinearSC::shoot(ProyectileType prType)
{
	Vector2D spawndir(sin(turret_->getRotation() / 180.0*M_PI) * 100, -cos(turret_->getRotation() / 180.0*M_PI) * 100);
	Vector2D spawnpoint = Vector2D(turret_->getCenter().x + spawndir.x, turret_->getCenter().y + spawndir.y);

	ProyectilePool::GetInstance()->addProyectile(spawnpoint,
		Vector2D(sin(turret_->getRotation()/180.0*M_PI), -cos(turret_->getRotation()/180.0*M_PI)), prType);
}

