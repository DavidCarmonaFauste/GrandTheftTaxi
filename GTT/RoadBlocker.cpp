#include "RoadBlocker.h"

RoadBlocker::RoadBlocker () {
	setPosition (ROAD_BLOCKER_POS);
	setHeight (ROAD_BLOCKER_HEIGHT);
	setWidth (ROAD_BLOCKER_WIDTH);

	// Sprite
	sprite_ = new Sprite (ROAD_BLOCKER_INFO.idlePath, width_, height_, ROAD_BLOCKER_POS.x, ROAD_BLOCKER_POS.y);
	addRenderComponent (sprite_);

	// Physics
	phyO_ = new PhysicObject(b2_staticBody, width_, height_, position_.x, position_.y);
	phyO_->setCollisions(0, TILE_CATEGORY);
	phyO_->getBody()->SetUserData(this);
	phyO_->getBody ()->SetTransform (position_.Multiply (PHYSICS_SCALING_FACTOR), 0);
	addLogicComponent(phyO_);
}


RoadBlocker::~RoadBlocker () {
}


void RoadBlocker::removeBlocker () {
	setActive (false);
	phyO_->getBody ()->SetActive (false);
}
