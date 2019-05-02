#pragma once
#include "IAMovementBehaviour.h"
#include "NodeMap.h"
#include <vector>

class PhysicObject;

class IAFollow :
	public IAMovementBehaviour
{
public:
	IAFollow(PhysicObject* ph, GameObject* o, NodeMap* districtMap, int patrolSpeed) :IAMovementBehaviour(ph, o, districtMap, patrolSpeed) {};
	virtual void update(GameObject* o, Uint32 deltaTime);
	virtual ~IAFollow();
};

