#include "ProjectilePool.h"

ProjectilePool* ProjectilePool::instance_ = nullptr;

ProjectilePool::ProjectilePool()
{
	for (int i = 0; i < MAX_PROJECTILES; i++) {
		projectiles_[i].setActive(false);
	}
}
void ProjectilePool::update(Uint32 time) {
	for (int i = 0; i < MAX_PROJECTILES; i++)
		if (projectiles_[i].isActive()) {
			projectiles_[i].update(time);
		}
}
void ProjectilePool::render(Uint32 time) {
	for (int i = 0; i < MAX_PROJECTILES; i++)
		if (projectiles_[i].isActive()) {
			projectiles_[i].render(time);
		}
}
Projectile* ProjectilePool::addProjectile(Vector2D pos, Vector2D vel, projectileType type, double lifeTime, double damage) {
	Projectile* e = getUnusedProjectile();
	if (e != nullptr) {
		e->setVelocity(vel);
		e->setPosition(Vector2D(pos.getX()-e->getWidth()/2, pos.getY()-e->getHeight()/2));
		e->SetDamage(damage);
		e->SetLifeTime(lifeTime);
		e->SetAnimation(type);
		e->setActive(true);
	}
	return e;
}

Projectile* ProjectilePool::getUnusedProjectile() {
	for (int i = 0; i < MAX_PROJECTILES; i++)
		if (!projectiles_[i].isActive()) {
			return &projectiles_[i];
		}

	return nullptr;
}

ProjectilePool::~ProjectilePool()
{
}
