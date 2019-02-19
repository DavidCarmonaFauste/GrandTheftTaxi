#pragma once
#include "LogicComponent.h"

class PhysicObject :
	public LogicComponent
{
public:
	PhysicObject(b2BodyType type, int w, int h);
	virtual ~PhysicObject();
	virtual void update(GameObject* o, Uint32 deltaTime);

private:
	b2Body* body_;
	b2BodyDef bodyDef_;

	b2FixtureDef fixtureDef_;
	b2PolygonShape shape_;
};

