#pragma once
#include "AimComponent.h"
class AimAtTaxi : public AimComponent
{
public:
	AimAtTaxi() {};
	virtual ~AimAtTaxi();
	virtual void update(GameObject* o, Uint32 deltaTime);

};

