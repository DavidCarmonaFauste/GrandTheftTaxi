#pragma once
#include "LogicComponent.h"
class NaturalMove  : public LogicComponent
{
public:
	NaturalMove();
	virtual void update(GameObject* o, Uint32 deltaTime);
	virtual ~NaturalMove();
};

