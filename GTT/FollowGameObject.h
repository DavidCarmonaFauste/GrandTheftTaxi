#pragma once

#include "LogicComponent.h"


class FollowGameObject :
	public LogicComponent
{
public:
	FollowGameObject(GameObject* objectToFollow);
	~FollowGameObject();

	virtual void update(GameObject *o, Uint32 deltaTime) override;

private:
	GameObject* objectToFollow_;
};

