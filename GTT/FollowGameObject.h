#pragma once

#include "LogicComponent.h"


class FollowGameObject :public LogicComponent
{
public:
	FollowGameObject(GameObject* objectToFollow, Vector2D offset = Vector2D(0,0));
	~FollowGameObject();

	virtual void update(GameObject *o, Uint32 deltaTime) override;

private:
	GameObject* objectToFollow_;
	Vector2D offset_;
};

