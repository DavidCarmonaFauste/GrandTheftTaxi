#include "LinearSC.h"
#include "ProjectilePool.h"

#define PI 3.14159265359


void LinearSC::shoot()
{
	ProjectilePool::GetInstance()->addProjectile(turret_->getCenter(),
		Vector2D(turret_->GetSpeed()*sin(turret_->getRotation()/180.0*PI), -turret_->GetSpeed()*cos(turret_->getRotation()/180.0*PI)),
		turret_->GetProjectileType(), turret_->GetLifeTime(), turret_->GetDamage());
}

