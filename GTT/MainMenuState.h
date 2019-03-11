#pragma once
#include "GameState.h"
#include "Vehicle.h"
class MainMenuState :
	public GameState
{
public:
	MainMenuState();
	virtual ~MainMenuState();


protected:
	Vehicle* vehicle_;

private:


};

