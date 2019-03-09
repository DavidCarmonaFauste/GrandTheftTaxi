#pragma once
#include "InputComponent.h"
#include "LogicComponent.h"
class ControlType :
	public InputComponent, public LogicComponent
{
public:
	ControlType();
	virtual ~ControlType();
};

