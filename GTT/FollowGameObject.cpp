#include "FollowGameObject.h"



FollowGameObject::FollowGameObject(GameObject* objectToFollow) {
	objectToFollow_ = objectToFollow;
}

FollowGameObject::~FollowGameObject() {
	objectToFollow_ = nullptr;
}


void FollowGameObject::update(GameObject * o, Uint32 deltaTime) {
	o->setPosition(objectToFollow_->getPosition());
}
