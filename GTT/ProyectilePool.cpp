#include "ProyectilePool.h"



ProyectilePool::ProyectilePool()
{
	for (int i = 0; i < MAX_PROYECTILES; i++) {
		proyectiles_[i].setActive(false);
	}
}
void ProyectilePool::update(Uint32 time) {
	for (int i = 0; i < MAX_PROYECTILES; i++)
		if (proyectiles_[i].isActive()) {
			proyectiles_[i].update(time);
		}
}
void ProyectilePool::render(Uint32 time) {
	for (int i = 0; i < MAX_PROYECTILES; i++)
		if (proyectiles_[i].isActive()) {
			proyectiles_[i].render(time);
		}
}
Proyectile* ProyectilePool::addProyectile(Vector2D pos, Vector2D vel, proyectileType type, double lifeTime, double damage) {
	Proyectile* e = getUnusedProyectile();
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

Proyectile* ProyectilePool::getUnusedProyectile() {
	for (int i = 0; i < MAX_PROYECTILES; i++)
		if (!proyectiles_[i].isActive()) {
			return &proyectiles_[i];
		}

	return nullptr;
}

ProyectilePool::~ProyectilePool()
{
}
