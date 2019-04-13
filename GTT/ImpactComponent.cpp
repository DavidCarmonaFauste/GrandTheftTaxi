#include "ImpactComponent.h"
#include "Vehicle.h"

ImpactComponent::ImpactComponent(Proyectile * o)
{
	o_ = o;
}

void ImpactComponent::Impact(b2Contact * contact)
{
	if (o_->getPhysicsObject() != nullptr) {
		b2Body* body = o_->getPhysicsObject()->getBody();
		b2Body* taxiBody = Vehicle::GetInstance()->GetPhyO()->getBody();

		if (contact->GetFixtureA()->GetBody() == body || contact->GetFixtureB()->GetBody() == body) {
			o_->setActive(false);
		}
	}
}

ImpactComponent::~ImpactComponent()
{
}
