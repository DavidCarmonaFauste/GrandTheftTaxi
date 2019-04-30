#include "ImpactComponent.h"
#include "Vehicle.h"
#include "Enemy.h"

ImpactComponent::ImpactComponent(Proyectile * o)
{
	o_ = o;
}

void ImpactComponent::Impact(b2Contact * contact)
{
	if (o_->getPhysicsObject() != nullptr) {
		b2Body* body = o_->getPhysicsObject()->getBody();

		if (contact->GetFixtureA()->GetBody() == body || contact->GetFixtureB()->GetBody() == body) {
			o_->DeactivateBullet();
			Enemy* e = (Enemy*)contact->GetFixtureA()->GetBody()->GetUserData();
			if(e==nullptr)
				e = (Enemy*)contact->GetFixtureB()->GetBody()->GetUserData();
			if (e != nullptr && o_->isAnEnemy()) {
				e->Damage(o_->GetDamage());
			} else
			if (o_->isAnEnemy() && (contact->GetFixtureA()->GetBody() == Vehicle::getInstance()->GetPhyO()->getBody() || contact->GetFixtureB()->GetBody() == Vehicle::getInstance()->GetPhyO()->getBody()))
 				Vehicle::getInstance()->getHealthComponent()->damage(o_->GetDamage());
		}
	}
}

ImpactComponent::~ImpactComponent()
{
}
