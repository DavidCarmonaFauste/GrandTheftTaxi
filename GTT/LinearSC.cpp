#include "LinearSC.h"
#include "ProyectilePool.h"

LinearSC::LinearSC(Turret * turret, double innac, int prob) :ShootComponent(turret)
{
	innacuracy_ = innac;
	probab_ = prob;
}

void LinearSC::shoot(ProyectileInfo prType)
{
	int r = rand() % 100;
	double innacuracy = 0;
	if (r <= probab_) {
		if (r <= probab_ / 2)
			innacuracy = -innacuracy_;
		else
			innacuracy = innacuracy_;
	}
	Vector2D spawndir(sin(turret_->getRotation() / 180.0*M_PI) * 100, -cos(turret_->getRotation() / 180.0*M_PI) * 100);
	Vector2D spawnpoint = Vector2D(turret_->getCenter().x + spawndir.x, turret_->getCenter().y + spawndir.y);

	ProyectilePool::GetInstance()->addProyectile(spawnpoint,
		Vector2D(sin((turret_->getRotation()+ innacuracy)/180.0*M_PI), -cos((turret_->getRotation()+ innacuracy)/180.0*M_PI)), prType);
}

