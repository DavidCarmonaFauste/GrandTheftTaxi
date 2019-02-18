#include "PhysicObject.h"


PhysicObject::PhysicObject(b2BodyType& type)
{
	bodyDef_ = new b2BodyDef();
	bodyDef_->position.Set(0,0);
	bodyDef_->type = type;
	//body_ = Game::GetWorld()->CreateBody(bodyDef_);
}


PhysicObject::~PhysicObject()
{
}

void PhysicObject::update(GameObject * o, Uint32 deltaTime)
{
}
