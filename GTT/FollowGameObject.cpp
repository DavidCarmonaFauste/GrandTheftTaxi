#include "FollowGameObject.h"



FollowGameObject::FollowGameObject(GameObject* objectToFollow, Vector2D offset) {
	objectToFollow_ = objectToFollow;
	offset_ = offset;
}

FollowGameObject::~FollowGameObject() {
	objectToFollow_ = nullptr;
}


void FollowGameObject::update(GameObject * o, Uint32 deltaTime) {
	o->setPosition(Vector2D(objectToFollow_->getCenter().x - o->getWidth() / 2, objectToFollow_->getCenter().y - o->getHeight() / 2) + offset_);
}
