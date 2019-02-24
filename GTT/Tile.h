#pragma once

#include "Container.h"
#include "PhysicObject.h"
#include "Sprite.h"

class Tile : public Container {
public:
	Tile(Texture* texture, SDL_Rect* dest, SDL_Rect* clip, uint32_t id, bool collision);
	virtual ~Tile();

	bool isBodyActive();
	void setBodyActive(bool a);

	Sprite* getSprite();
	PhysicObject* getPhysicObject();

private:
	Sprite* sprite_;
	PhysicObject* phyO_;

	uint32_t id_;
};

