#include "MainMenuState.h"



MainMenuState::MainMenuState()
{
	v = new Vehicle(Resources::Taxi);
	this->stage_.push_back(v);
}


MainMenuState::~MainMenuState()
{
}
