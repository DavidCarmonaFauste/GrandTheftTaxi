#include "Resources.h"
#include "MainMenuState.h"



Resources* Resources::singleton_ = nullptr;

Resources::Resources() {
	//par {string, states}


	physicsScalingFactor = 0.2;

	vehicles_ = {
		{Taxi, "../Assets/sprites/taxi.png", "../Assets/sprites/default.png", "../Assets/sprites/default.png", 50, 100}
	};

	sounds_ = {
		{Default_Sound, "../Assets/sounds/default.wav"}
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
	mainMenuState_ = new MainMenuState();
	STATES_.insert(std::pair<string, GameState*>(NAME_MAINMENU_STATE, mainMenuState_));
}

