#pragma once
#include "Container.h"
#include "PhysicObject.h"
#include "CustomContactListener.h"

class Trigger :	public Container, public Observable {
public:
	Trigger(int w, int h, int x, int y);
	virtual ~Trigger();

	PhysicObject* getPhysicsObject();	

private:
	PhysicObject* phyO_;

	CustomContactListener *contactListener_;
};

