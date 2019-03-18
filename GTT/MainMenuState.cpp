#include "MainMenuState.h"



MainMenuState::MainMenuState()
{
	stage_.push_back (new Button (mainStateCallback, Resources::MainMenuPlay));
	stage_.push_back (new Button (exitGameCallback, Resources::MainMenuExit));
}


MainMenuState::~MainMenuState()
{
	while (!stage_.empty ()) {
		delete stage_.back (); 
		stage_.back () = nullptr;
		stage_.pop_back ();
	}

}
