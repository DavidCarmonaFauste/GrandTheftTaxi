#include "BounceImC.h"
#include "Vehicle.h"

BounceImC::BounceImC(Proyectile * o, int maxBounces): ImpactComponent(o)
{
	maxBounces_ = maxBounces;
	bounces_ = 0;
}

void BounceImC::Impact(b2Contact* contact)
{
	if (o_->getPhysicsObject() != nullptr) {
		b2Body* body = o_->getPhysicsObject()->getBody();
		b2Body* taxiBody = Vehicle::GetInstance()->GetPhyO()->getBody();

		if ((contact->GetFixtureA()->GetBody() == body || contact->GetFixtureA()->GetBody() != taxiBody)
			&& (contact->GetFixtureB()->GetBody() == body || contact->GetFixtureB()->GetBody() != taxiBody)) {
			if (bounces_ < maxBounces_)
				bounces_++;
			else {
				o_->setActive(false);
				bounces_ = 0;
			}
		}
	}
}

BounceImC::~BounceImC()
{
}
