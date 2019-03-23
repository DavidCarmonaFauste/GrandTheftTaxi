#include "ProyectilePool.h"
#include "Resources.h"

ProyectilePool* ProyectilePool::instance_ = nullptr;

ProyectilePool::ProyectilePool()
{
	for (auto& proyectile : proyectiles_) {
		proyectile.setActive(false);
	}
	
}
void ProyectilePool::update(Uint32 time) {
	for (auto& proyectile : proyectiles_) {
		if (proyectile.isActive()) {
			proyectile.update(time);
		}
	}
}
void ProyectilePool::render(Uint32 time) {
	for (auto& proyectile : proyectiles_)
	{
		if (proyectile.isActive()) {
			proyectile.render(time);
		}
	}
}
Proyectile* ProyectilePool::addProyectile(Vector2D pos, Vector2D vel, proyectileType type, double lifeTime, double damage) {
	Proyectile* e = getUnusedProyectile();
	if (e != nullptr) {
		e->GetPhyO()->getBody()->SetTransform(Vector2D(pos.x*Resources::getInstance()->physicsScalingFactor, pos.y*Resources::getInstance()->physicsScalingFactor), 0);
		e->GetPhyO()->getBody()->SetLinearVelocity(vel);
		e->SetDamage(damage);
		e->SetLifeTime(lifeTime);
		e->SetAnimation(type);
		e->SetBirth(SDL_GetTicks());
		e->setActive(true);
	}
	return e;
}

Proyectile* ProyectilePool::getUnusedProyectile() {

	for (auto& proyectile : proyectiles_) {
		if (!proyectile.isActive()) {
			return &proyectile;
		}
	}
	return nullptr;
}

ProyectilePool::~ProyectilePool()
{
}
