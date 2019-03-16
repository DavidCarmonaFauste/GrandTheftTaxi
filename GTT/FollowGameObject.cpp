#include "FollowGameObject.h"



FollowGameObject::FollowGameObject(GameObject* objectToFollow) {
	objectToFollow_ = objectToFollow;
}

FollowGameObject::~FollowGameObject() {
	objectToFollow_ = nullptr;
}


void FollowGameObject::update(GameObject * o, Uint32 deltaTime) {
	o->setPosition(Vector2D(objectToFollow_->getCenter().getX() - o->getWidth() / 2, objectToFollow_->getCenter().getY() - o->getHeight() / 2));
}
