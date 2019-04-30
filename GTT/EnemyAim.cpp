#include "EnemyAim.h"
#include "Enemy.h"
#include "Vehicle.h"
#include "Turret.h"

EnemyAim::EnemyAim()
{
}

void EnemyAim::update(GameObject * o, Uint32 deltaTime)
{
	Enemy* e = static_cast<Enemy*>(o);
	if (e->taxiOnRange()) {
		double disX = Vehicle::getInstance()->getCenter().x - o->getCenter().x;
		double disY = Vehicle::getInstance()->getCenter().y - o->getCenter().y;
		double degrees = acos(-disY / (sqrt(pow(disX, 2) + pow(disY, 2))));
		e->getTurret()->setRotation(degrees * 180.0 / M_PI);
		if (disX < 0)
			e->setRotation(-e->getRotation());
	}
}


EnemyAim::~EnemyAim()
{
}
