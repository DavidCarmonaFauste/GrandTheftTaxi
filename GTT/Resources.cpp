#include "Resources.h"

// States
#include "MainMenuState.h"
#include "MainState.h"


Resources* Resources::singleton_ = nullptr;

Resources::Resources() {
	
}



Resources::~Resources() {

}

Resources * Resources::getInstance() {
	if (singleton_ == nullptr) {
		singleton_ = new Resources();
	}

	return singleton_;
}

void Resources::initStates() {
	// Main menu
	STATES_.insert(std::pair<string, GameState*>(NAME_MAINMENU_STATE, new MainMenuState()));

	// Main game
	STATES_.insert(std::pair<string, GameState*>(NAME_MAIN_STATE, new MainState()));
}
