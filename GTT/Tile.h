#pragma once

#include "Container.h"
#include "PhysicObject.h"
#include "Animation.h"

class Tile : public Container {
public:
	Tile(string path, int x, int y, int width, int height, bool collision);
	virtual ~Tile();

	bool isBodyActive();
	void setBodyActive(bool a);
	PhysicObject* getPhysicObject();

private:
	Animation* sprite_;
	PhysicObject* phyO_;
};

