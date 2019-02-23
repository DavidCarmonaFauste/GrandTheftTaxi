#include "Tile.h"

Tile::Tile(string path, int x, int y, int width, int height, bool collision) {
	// GameObject defaults
	setPosition(Vector2D(x, y));
	setWidth(width);
	setHeight(height);

	// Sprite
	sprite_ = new Animation();
	addRenderComponent(sprite_);
	sprite_->loadAnimation(path, "default");
	sprite_->playAnimation("default", 0);

	// Physics object
	phyO_ = new PhysicObject(b2_staticBody, width, height);
	addLogicComponent(phyO_);
	phyO_->getBody()->SetActive(collision);
}


Tile::~Tile() {
	delete sprite_; sprite_ = nullptr;
	delete phyO_; phyO_ = nullptr;
}

bool Tile::isBodyActive() {
	return phyO_->getBody()->IsActive();
}

void Tile::setBodyActive(bool a) {
	phyO_->getBody()->SetActive(a);
}

PhysicObject* Tile::getPhysicObject() {
	return phyO_;
}
