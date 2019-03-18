#include "Resources.h"

// States
#include "MainMenuState.h"
#include "MainState.h"


Resources* Resources::singleton_ = nullptr;

Resources::Resources() {
	physicsScalingFactor = 0.2;

	vehicles_ = {
		{Taxi, PATH_TAXI, PATH_DEFAULT_TEXTURE, PATH_DEFAULT_TEXTURE, 50, 100}
	};

	sounds_ = {
		{Default_Sound, PATH_DEFAULT_SOUND}
	};

	music_ = {
		{Default_Music, PATH_DEFAULT_SOUND}
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

