#include "ProyectilePool.h"
#include "Resources.h"
#include "GunProyectile.h"
#include "ShotGunProyectile.h"

ProyectilePool* ProyectilePool::instance_ = nullptr;

ProyectilePool::ProyectilePool()
{
	for (int i = standB; i < standB + nStandBullets; i++) {//proyectiles standar
		proyectiles_.push_back(new GunProyectile());
	}
	for (int i = sgB; i < sgB + nShotGunBullets; i++) {//proyectiles shotgun
		proyectiles_.push_back(new ShotGunProyectile());
	}
	for (int i = spstandB; i < spstandB + nSpecStandBullets; i++) {//proyectiles standarespeciales
		proyectiles_.push_back(new Proyectile());
	}
	for (int i = spsgB; i < spsgB + nSpecSGBullets; i++) {//proyectiles escopetaespeciales
		proyectiles_.push_back(new Proyectile());
	}

}
void ProyectilePool::update(Uint32 time) {
	for (auto proyectile : proyectiles_) {
		if (proyectile->isActive()) {
			proyectile->update(time);
		}
	}
}
void ProyectilePool::render(Uint32 time) {
	for (auto& proyectile : proyectiles_)
	{
		if (proyectile->isActive()) {
			proyectile->render(time);
		}
	}
}

Proyectile * ProyectilePool::addStandardB(Vector2D pos, Vector2D vel)
{
	Proyectile* e = getUnusedStandardB();
	if (e != nullptr) {
		e->GetPhyO()->getBody()->SetTransform(Vector2D(pos.x*Resources::getInstance()->physicsScalingFactor, pos.y*Resources::getInstance()->physicsScalingFactor), 0);
		e->GetPhyO()->getBody()->SetLinearVelocity(Vector2D(vel.x * e->GetSpeed(), vel.y* e->GetSpeed()));
		e->SetBirth(SDL_GetTicks());
		e->setActive(true);
	}
	return e;
}

Proyectile * ProyectilePool::addShotgunB(Vector2D pos, Vector2D vel)
{
	Proyectile* e = getUnusedShotGunB();
	if (e != nullptr) {
		e->GetPhyO()->getBody()->SetTransform(Vector2D(pos.x*Resources::getInstance()->physicsScalingFactor, pos.y*Resources::getInstance()->physicsScalingFactor), 0);
		e->GetPhyO()->getBody()->SetLinearVelocity(Vector2D(vel.x * e->GetSpeed(), vel.y* e->GetSpeed()));
		e->SetBirth(SDL_GetTicks());
		e->setActive(true);
	}
	return e;
}

Proyectile * ProyectilePool::getUnusedStandardB()
{
	for (int i = standB; i < standB + nStandBullets; i++) {
		if (!proyectiles_[i]->isActive()) {
			return proyectiles_[i];
		}
	}
	return nullptr;
}

Proyectile * ProyectilePool::getUnusedShotGunB()
{
	for (int i = sgB; i < sgB + nShotGunBullets; i++) {
		if (!proyectiles_[i]->isActive()) {
			return proyectiles_[i];
		}
	}
	return nullptr;
}

ProyectilePool::~ProyectilePool()
{
}
