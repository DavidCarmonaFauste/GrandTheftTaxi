#include "ProyectilePool.h"
#include "Resources.h"

ProyectilePool* ProyectilePool::instance_ = nullptr;

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
			//cout << proyectiles_[i].GetPhyO()->getBody()->GetTransform().p.x << endl;
			//cout << proyectiles_[i].GetPhyO()->getBody()->GetLinearVelocity().x << " / " << proyectiles_[i].GetPhyO()->getBody()->GetLinearVelocity().y << endl;
			//cout << proyectiles_[i].getPosition().x << " : ";
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
		cout << vel.x << " : ";
		e->GetPhyO()->getBody()->SetTransform(Vector2D(pos.x*Resources::getInstance()->physicsScalingFactor, pos.y*Resources::getInstance()->physicsScalingFactor), 0);
		e->GetPhyO()->getBody()->SetLinearVelocity(vel);
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
