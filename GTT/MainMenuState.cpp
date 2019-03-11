#include "MainMenuState.h"



MainMenuState::MainMenuState()
{
	vehicle_ = new Vehicle(Resources::VehicleId::Taxi);
}


MainMenuState::~MainMenuState()
{
}
