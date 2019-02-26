#pragma once
#include "LogicComponent.h"
#include "Health.h"

class Respawn :	public LogicComponent {
public:
	Respawn(Health* health);
	virtual ~Respawn();
};

