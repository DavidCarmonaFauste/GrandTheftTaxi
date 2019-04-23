#include "EnemyPool.h"


EnemyPool* EnemyPool::instance_ = nullptr;

EnemyPool::EnemyPool()
{

}
Enemy * EnemyPool::getUnusedEnemy()
{
	for (auto& proyectile : enemies_) {
		if (!proyectile.isActive()) {
			return &proyectile;
		}
	}
	return nullptr;
}
void EnemyPool::update(Uint32 time) {
	for (auto& enemy : enemies_) {
		if (enemy.isActive()) {
			enemy.update(time);
		}
	}
}
void EnemyPool::render(Uint32 time) {
	for (auto& proyectile : enemies_)
	{
		if (proyectile.isActive()) {
			proyectile.render(time);
		}
	}
}

Enemy * EnemyPool::addEnemy(Vector2D pos, Vector2D vel, ProyectileInfo prType)
{
	Enemy* e;
	e = getUnusedEnemy();
	if (e != nullptr) {
		e->ChangeBulletType(prType);
		/*e->GetPhyO()->getBody()->SetTransform(Vector2D(pos.x*PHYSICS_SCALING_FACTOR, pos.y*PHYSICS_SCALING_FACTOR), 0);
		e->GetPhyO()->getBody()->SetLinearVelocity(Vector2D(vel.x * e->GetSpeed(), vel.y* e->GetSpeed()));
		e->SetBirth(SDL_GetTicks());*/
		e->setActive(true);
	}
	return e;
}


EnemyPool::~EnemyPool()
{
}

