#include "BounceImC.h"
#include "Vehicle.h"
#include "Enemy.h"

BounceImC::BounceImC(Proyectile * o, int maxBounces): ImpactComponent(o)
{
	maxBounces_ = maxBounces;
	bounces_ = 0;
}

void BounceImC::Impact(b2Contact* contact)
{
	if (o_->getPhysicsObject() != nullptr) {
		b2Body* body = o_->getPhysicsObject()->getBody();
		b2Body* taxiBody = Vehicle::getInstance()->GetPhyO()->getBody();

		if (contact->GetFixtureA()->GetBody() == body || contact->GetFixtureB()->GetBody() == body) {
			Enemy* e = (Enemy*)contact->GetFixtureA()->GetBody()->GetUserData();
			if (e == nullptr) e = (Enemy*)contact->GetFixtureB()->GetBody()->GetUserData();
			if (e != nullptr) {
				e->Damage(o_->GetDamage());
				o_->DeactivateBullet();
			}
			else {
				if (bounces_ < maxBounces_) bounces_++;
				else {
					o_->DeactivateBullet();
					bounces_ = 0;
				}
			}
		}
	}
}

BounceImC::~BounceImC()
{
}
