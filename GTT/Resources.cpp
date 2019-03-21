#include "Resources.h"

// States
#include "MainMenuState.h"
#include "MainState.h"


Resources* Resources::singleton_ = nullptr;

Resources::Resources() {
	physicsScalingFactor = 0.2;

	vehicles_ = {
		{Taxi, "../Assets/sprites/taxi.png", "../Assets/sprites/default.png", "../Assets/sprites/default.png", 200, 400}
	};

	sounds_ = {
		{Default_Sound, "../Assets/sounds/default.wav"}
	};

	music_ = {
		{Default_Music, "../Assets/sounds/default.wav"}
	};

	fonts_ = {
		{Default_Font, "../Assets/fonts/lato_regular.ttf"}
	};
}



Resources::~Resources() {
	//delete introState_;
	//introState_ = nullptr;
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

