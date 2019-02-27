#pragma once
#include "LogicComponent.h"

class PhysicObject :
	public LogicComponent
{
public:
	PhysicObject(b2BodyType type, int w, int h, int x, int y, float32 angle = 0, Vector2D origin = Vector2D(0.5, 0.5));
	virtual ~PhysicObject();
	virtual void update(GameObject* o, Uint32 deltaTime);

	b2Body* getBody();

private:
	b2Body* body_;
	b2BodyDef bodyDef_;
	Vector2D visualSize_;
	Vector2D origin_;

	b2FixtureDef fixtureDef_;
	b2PolygonShape shape_;
};

