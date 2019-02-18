#pragma once
#include "LogicComponent.h"

class PhysicObject :
	public LogicComponent
{
public:
	PhysicObject(b2BodyType& type);
	virtual ~PhysicObject();
	virtual void update(GameObject* o, Uint32 deltaTime);

private:
	b2Body* body_;
	b2BodyDef* bodyDef_;
};

