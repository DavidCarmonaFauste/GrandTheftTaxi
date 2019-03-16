#include "Tile.h"

Tile::Tile(Texture* texture, SDL_Rect* dest, SDL_Rect* clip, uint32_t id, bool collision) {
	// GameObject defaults
	setPosition(Vector2D(dest->x, dest->y));
	setWidth(dest->w);
	setHeight(dest->h);

	// Sprite
	sprite_ = new Sprite(texture);
	sprite_->setClipRect(clip);
	addRenderComponent(sprite_);

	// Physics object
	if (collision) {
		phyO_ = new PhysicObject(b2_staticBody, dest->w * Resources::getInstance()->physicsScalingFactor,
			dest->h * Resources::getInstance()->physicsScalingFactor,
			position_.getX(), position_.getY());
		addLogicComponent(phyO_); // Not used unless tile update function gets called (very inneficient)
	}

	// Tile
	id_ = id;
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

Sprite * Tile::getSprite() {
	return sprite_;
}

PhysicObject* Tile::getPhysicObject() {
	return phyO_;
}
